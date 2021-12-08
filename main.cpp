#include <iostream>
#include <chrono>
#include <thread>

#include "engine/age.h"
#include "engine/Scene.h"
#include "engine/components/EngineSystems.h"
#include "engine/renderer/RenderComponents/impl/CharacterProp.h"

[[noreturn]] void DEBUG_PAUSE() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

class DefaultDrawScene : public AGE::Scene {
  public:
    DefaultDrawScene(const std::string &name) : AGE::Scene(name) {}
    ~DefaultDrawScene() override = default;
    void init() override {}
    void onActivate() override {}
    void onDeactivate() override {}
    void teardown() override {}
};

class Application : public AGE::CursesApplicationContext {
  public:
    Application(int width, int height) : AGE::CursesApplicationContext(width, height) {}
    ~Application() override = default;
    void init() override {
        AGE::CursesApplicationContext::init();
        using namespace AGE;

        Scene *scene = getSceneManager()->createScene<DefaultDrawScene>("Draw_Scene");

        using namespace AGE;
        // component registration
        scene->getRegistry()->registerComponent<Components::TransformComponent>();
        scene->getRegistry()->registerComponent<Components::AsciiRenderComponent>();

        // ascii renderer setup and registration
        auto asciiRenderSystem = scene->getRegistry()->registerSystem<Systems::AsciiRenderSystem>(scene->getRegistry());
        asciiRenderSystem->setRenderer(asciiRenderer.get());

        ECS::Archetype asciiRendererSystemArchetype;
        asciiRendererSystemArchetype
            .push_back(scene->getRegistry()->getComponentType<Components::TransformComponent>());
        asciiRendererSystemArchetype
            .push_back(scene->getRegistry()->getComponentType<Components::AsciiRenderComponent>());
        scene->getRegistry()->setSystemArchetype<Systems::AsciiRenderSystem>(asciiRendererSystemArchetype);

        // entity creation
        Renderer::AsciiRenderProp *charProp = new Renderer::CharacterProp('@');
        ECS::Entity testEntity = scene->createEntity();
        testEntity.addComponent(Components::TransformComponent(vec3<int>(5, 5, 0)));
        testEntity.addComponent(Components::AsciiRenderComponent(charProp));

        std::unique_ptr<EventDispatcher>
            renderDispatcher =
            std::make_unique<FunctionEventDispatcher<Events::EngineDrawEvent>>(
                [asciiRenderSystem](Events::EngineDrawEvent *event, EventQueue *queue) {
                  asciiRenderSystem->render();
                });
        engineEventQueue->registerEventDispatcher<Events::EngineDrawEvent>(renderDispatcher.get());
        eventListeners.push_back(std::move(renderDispatcher));
    }
};

// resolve entry point extern
std::unique_ptr<AGE::ApplicationContext> gameEntryPoint(int argc, char *argv[]) {
    return std::make_unique<Application>(80, 25);
}
