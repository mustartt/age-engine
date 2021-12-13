//
// Created by henry on 2021-12-12.
//

#ifndef FINAL_PROJECT_EXAMPLES_FEATUREDEMO_SCENES_INTROSCENE_H_
#define FINAL_PROJECT_EXAMPLES_FEATUREDEMO_SCENES_INTROSCENE_H_

#include <Scene.h>
#include <events/Event.h>
#include <renderer/RenderComponents/AsciiRenderProp.h>

namespace FeatureDemo {

using namespace AGE;

class IntroScene : public Scene {
    using ResourceManager = std::unordered_map<std::string, std::unique_ptr<Renderer::AsciiRenderProp>>;
    std::unordered_map<std::string, std::unique_ptr<EventDispatcher>> eventListeners;
    EventQueue *engineEventQueue;
    EventQueue *applicationEventQueue;
    ResourceManager *resources;
  public:
    IntroScene(const std::string &name,
               AGE::EventQueue *engine,
               AGE::EventQueue *application,
               ResourceManager *resources) : Scene(name), engineEventQueue(engine),
                                             applicationEventQueue(application),
                                             resources(resources) {}
    ~IntroScene() override = default;
    void init() override;
    void setup() override;
    void onActivate() override;
    void onDeactivate() override;
    void teardown() override;
};

}

#endif //FINAL_PROJECT_EXAMPLES_FEATUREDEMO_SCENES_INTROSCENE_H_
