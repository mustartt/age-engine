//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_ENTRY_ENTRYPOINT_H_
#define FINAL_PROJECT_ENGINE_ENTRY_ENTRYPOINT_H_
#ifdef COMPILE_AS_ENGINE

#include <memory>
#include "../ncurses/CursesContextManager.h"
#include "../events/Event.h"
#include "../renderer/RenderTarget.h"
#include "../renderer/AsciiRenderer.h"
#include "../events/engine_events/EngineEvent.h"
#include "../SceneManager.h"

namespace AGE {

class ApplicationContext {
  public:
    ApplicationContext() = default;
    virtual ~ApplicationContext() = default;
    virtual void run() = 0;
    virtual void init() = 0;
    virtual void stop() = 0;
};

class CursesApplicationContext : public ApplicationContext {
  protected:
    int windowWidth;
    int windowHeight;
    std::unique_ptr<CursesContextManager> manager;

    std::unique_ptr<EventQueue> engineEventQueue;
    std::unique_ptr<EventQueue> applicationEventQueue;

    std::unique_ptr<Renderer::RenderTarget> renderTarget;
    std::unique_ptr<AsciiRenderer> asciiRenderer;

    std::unique_ptr<SceneManager> sceneManager;

    std::unordered_map<std::string, std::unique_ptr<EventDispatcher>> eventListeners;

    bool isRunning = true;
  public:
    CursesApplicationContext(int width, int height);
    ~CursesApplicationContext() override = default;

    [[nodiscard]] EventQueue *getEngineQueue() const { return engineEventQueue.get(); }
    [[nodiscard]] EventQueue *getApplicationQueue() const { return applicationEventQueue.get(); }

    void init() override;
    void run() override;
    void stop() override;

    SceneManager *getSceneManager() const { return sceneManager.get(); }
  private:
    void shutdownHandler(Events::EngineShutdownEvent *event, EventQueue *eventQueue) { isRunning = false; }
    void exitKeyHandler(Events::KeyPressedEvent *event, EventQueue *eventQueue); // debug: exits on p
    void changeSceneHandler(Events::SwitchSceneEvent *event, EventQueue *eventQueue);
};

}

extern std::unique_ptr<AGE::ApplicationContext> gameEntryPoint(int argc, char *argv[]);

#endif
#endif //FINAL_PROJECT_ENGINE_ENTRY_ENTRYPOINT_H_
