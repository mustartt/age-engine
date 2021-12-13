//
// Created by henry on 2021-12-12.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_SCENES_GAMESTARTSCENE_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_SCENES_GAMESTARTSCENE_H_

#include <Scene.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <renderer/RenderComponents/AsciiRenderProp.h>

namespace SpaceInvader {

using namespace AGE;

class GameStartScene : public Scene {
    using ResourceManager = std::unordered_map<std::string, std::unique_ptr<Renderer::AsciiRenderProp>>;
    std::unordered_map<std::string, std::unique_ptr<EventDispatcher>> eventListeners;
    EventQueue *engineEventQueue;
    EventQueue *applicationEventQueue;
    ResourceManager *resources;
  public:
    GameStartScene(const std::string &name,
                   EventQueue *engine,
                   EventQueue *application,
                   ResourceManager *resources);
    ~GameStartScene() override = default;
  private:
    void init() override;
    void setup() override;
    void onActivate() override;
    void onDeactivate() override;
    void teardown() override;
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_SCENES_GAMESTARTSCENE_H_
