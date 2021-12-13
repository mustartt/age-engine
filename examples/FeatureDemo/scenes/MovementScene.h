//
// Created by henry on 2021-12-12.
//

#ifndef FINAL_PROJECT_EXAMPLES_FEATUREDEMO_SCENES_MOVEMENTSCENE_H_
#define FINAL_PROJECT_EXAMPLES_FEATUREDEMO_SCENES_MOVEMENTSCENE_H_

#include <Scene.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <renderer/RenderComponents/AsciiRenderProp.h>
#include <renderer/RenderComponents/CharacterProp.h>

namespace FeatureDemo {

using namespace AGE;

class MovementScene : public Scene {
    using ResourceManager = std::unordered_map<std::string, std::unique_ptr<Renderer::AsciiRenderProp>>;
    std::unordered_map<std::string, std::unique_ptr<EventDispatcher>> eventListeners;
    EventQueue *engineEventQueue;
    EventQueue *applicationEventQueue;
    ResourceManager *resources;
  public:
    MovementScene(const std::string &name, EventQueue *engine, EventQueue *application, ResourceManager *resources)
        : Scene(name), engineEventQueue(engine),
          applicationEventQueue(application),
          resources(resources) {}
    ~MovementScene() override = default;
  private:
    void init() override;
    void setup() override;
    void onActivate() override;
    void onDeactivate() override;
    void teardown() override;
};

}

#endif //FINAL_PROJECT_EXAMPLES_FEATUREDEMO_SCENES_MOVEMENTSCENE_H_
