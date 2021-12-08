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

class TestScene : public AGE::Scene {
  public:
    void setup() override {
        using namespace AGE;

    }
    void teardown() override {

    }
};

class Application : public AGE::GameEntryPoint {
  public:
    Application() = default;
    ~Application() override = default;
    int run() override {
        using namespace AGE;
        CursesContextManager manager(80, 25);
        Renderer::RenderTarget *adapter = new Renderer::CursesRenderAdapter(manager.getRendererInstance());
        auto *renderer = new AsciiRenderer(adapter, 80, 25);

        Scene *scene = new TestScene();

        auto *sceneRegistry = scene->getRegistry();

        // component registration
        sceneRegistry->registerComponent<Components::TransformComponent>();
        sceneRegistry->registerComponent<Components::AsciiRenderComponent>();

        // ascii renderer setup and registration
        auto asciiRenderSystem = sceneRegistry->registerSystem<Systems::AsciiRenderSystem>(sceneRegistry);
        asciiRenderSystem->setRenderer(renderer);

        ECS::Archetype asciiRendererSystemArchetype;
        asciiRendererSystemArchetype.push_back(sceneRegistry->getComponentType<Components::TransformComponent>());
        asciiRendererSystemArchetype.push_back(sceneRegistry->getComponentType<Components::AsciiRenderComponent>());
        sceneRegistry->setSystemArchetype<Systems::AsciiRenderSystem>(asciiRendererSystemArchetype);

        // entity creation
        Renderer::AsciiRenderProp *charProp = new Renderer::CharacterProp('@');
        ECS::Entity testEntity = scene->createEntity();
        testEntity.addComponent(Components::TransformComponent(vec3<int>(5, 5, 0)));
        testEntity.addComponent(Components::AsciiRenderComponent(charProp));

        renderer->clear();
        asciiRenderSystem->render();
        renderer->draw();

        return 0;
    }
};

// resolve entry point extern
std::unique_ptr<AGE::GameEntryPoint> gameEntryPoint(int argc, char *argv[]) {
    return std::make_unique<Application>();
}
