//
// Created by henry on 2021-12-08.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_SCENES_MAINSCENE_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_SCENES_MAINSCENE_H_

#include <Scene.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <renderer/RenderComponents/AsciiRenderProp.h>
#include <renderer/RenderComponents/CharacterProp.h>

namespace SpaceInvader {

using namespace AGE;

class MainScene : public Scene {
    using ResourceManager = std::unordered_map<std::string, std::unique_ptr<Renderer::AsciiRenderProp>>;
    std::unordered_map<std::string, std::unique_ptr<EventDispatcher>> eventListeners;
    EventQueue *engineEventQueue;
    EventQueue *applicationEventQueue;
    ResourceManager *resources;
  public:
    MainScene(const std::string &name, EventQueue *engine, EventQueue *application, ResourceManager *resources)
        : Scene(name), engineEventQueue(engine),
          applicationEventQueue(application),
          resources(resources) {}
    ~MainScene() override = default;
  private:
    void init() override;
    void setup() override;
    void onActivate() override;
    void onDeactivate() override;
    void teardown() override;
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_SCENES_MAINSCENE_H_
