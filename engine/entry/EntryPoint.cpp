//
// Created by henry on 2021-12-07.
//
#ifdef COMPILE_AS_ENGINE

#include <chrono>
#include <thread>
#include "EntryPoint.h"
#include "../ncurses/CursesRenderAdapter.h"
#include "../SceneManager.h"

namespace AGE {

CursesApplicationContext::CursesApplicationContext(int width, int height)
    : windowWidth(width), windowHeight(height),
      manager(std::make_unique<CursesContextManager>()),
      engineEventQueue(std::make_unique<EventQueue>()),
      applicationEventQueue(std::make_unique<EventQueue>()),
      renderTarget(std::make_unique<Renderer::CursesRenderAdapter>(manager->getRendererInstance())),
      asciiRenderer(std::make_unique<AsciiRenderer>(renderTarget.get(), width, height)),
      sceneManager(std::make_unique<SceneManager>()),
      eventListeners{} {
    // shutdown event handler
    std::unique_ptr<EventDispatcher>
        shutdownDispatcher =
        std::make_unique<MemberEventDispatcher<CursesApplicationContext, Events::EngineShutdownEvent>>
            (this, &CursesApplicationContext::shutdownHandler);
    engineEventQueue->registerEventDispatcher<Events::EngineShutdownEvent>(shutdownDispatcher.get());
    eventListeners["shutdown"] = std::move(shutdownDispatcher);

    // debug: p keypress handler exists application
    std::unique_ptr<EventDispatcher>
        exitKeyDispatcher = std::make_unique<MemberEventDispatcher<CursesApplicationContext, Events::KeyPressedEvent>>
        (this, &CursesApplicationContext::exitKeyHandler);
    applicationEventQueue->registerEventDispatcher<Events::KeyPressedEvent>(exitKeyDispatcher.get());
    eventListeners["exit_key"] = std::move(exitKeyDispatcher);

    // switch scene handler
    std::unique_ptr<EventDispatcher>
        switchSceneDispatcher =
        std::make_unique<MemberEventDispatcher<CursesApplicationContext, Events::SwitchSceneEvent>>
            (this, &CursesApplicationContext::changeSceneHandler);
    applicationEventQueue->registerEventDispatcher<Events::SwitchSceneEvent>(switchSceneDispatcher.get());
    eventListeners["switch_scene"] = std::move(switchSceneDispatcher);
}

void CursesApplicationContext::init() {
    engineEventQueue->enqueue<Events::EngineInitEvent>();
    engineEventQueue->dispatchEvents();
}

void CursesApplicationContext::run() {
    auto delay = std::chrono::milliseconds(33);
    while (isRunning) {
        // queue up engine events
        engineEventQueue->enqueue<Events::EngineDrawEvent>();
        engineEventQueue->enqueue<Events::EngineUpdateEvent>(delay);

        // queue all user keyboard inputs
        manager->getKeyboardInstance()->captureInputs();
        std::optional<int> keycode = manager->getKeyboardInstance()->getKeycode();
        while (keycode) {
            applicationEventQueue->enqueue<Events::KeyPressedEvent>(keycode.value());
            keycode = manager->getKeyboardInstance()->getKeycode();
        }

        applicationEventQueue->dispatchEvents(); // dispatch application events second
        engineEventQueue->dispatchEvents(); // dispatch engine events first
        std::this_thread::sleep_for(delay);
    }
}

void CursesApplicationContext::stop() {
    engineEventQueue->registerEventDispatcher<Events::EngineShutdownEvent>(eventListeners["shutdown"].get());
    applicationEventQueue->registerEventDispatcher<Events::KeyPressedEvent>(eventListeners["exist_key"].get());
    applicationEventQueue->registerEventDispatcher<Events::SwitchSceneEvent>(eventListeners["switch_scene"].get());
}

void CursesApplicationContext::exitKeyHandler(Events::KeyPressedEvent *event, EventQueue *eventQueue) {
    if (event->getKeyCode() == 'p') {
        getEngineQueue()->enqueue<Events::EngineShutdownEvent>(0);
        getEngineQueue()->dispatchEvents();
    }
}

void CursesApplicationContext::changeSceneHandler(Events::SwitchSceneEvent *event, EventQueue *eventQueue) {

}

}

// GLOBAL ENTRY POINT FOR AGE ENGINE
int main(int argc, char *argv[]) {
    auto ptr = gameEntryPoint(argc, argv);
    ptr->init();
    ptr->run();
    ptr->stop();
    return 0;
}

#endif
