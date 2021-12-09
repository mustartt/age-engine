#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <utility>

#include "engine/data/vec2.h"
#include "engine/data/vec3.h"

#include "engine/age.h"
#include "engine/Scene.h"
#include "engine/components/EngineSystems.h"
#include "engine/renderer/RenderComponents/impl/CharacterProp.h"
#include "engine/renderer/RenderComponents/impl/BitMapProp.h"

[[noreturn]] void DEBUG_PAUSE() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

AGE::Renderer::BitMap createBitMap() {
    std::vector<std::string> img{
        "@  @@@@",
        "@  @   ",
        "@@@@@@@",
        "   @  @",
        "@@@@  @"
    };

    std::vector<std::pair<AGE::vec2<int>, char>> bitmap;

    for (int x = 0; x < img[0].size(); ++x) {
        for (int y = 0; y < img.size(); ++y) {
            if (img[y][x] == '@') {
                bitmap.emplace_back(AGE::vec2<int>(x - 3, y - 2), '@');
            }
        }
    }
    return bitmap;
}

class DefaultDrawScene : public AGE::Scene {
    std::unique_ptr<AGE::Renderer::AsciiRenderProp> prop;
  public:
    DefaultDrawScene(const std::string &name) : AGE::Scene(name) {}
    ~DefaultDrawScene() override = default;
    void init() override {
        prop = std::move(std::make_unique<AGE::Renderer::BitMapProp>(createBitMap()));
    }
    void onActivate() override {
        using namespace AGE;
        // entity creation
        ECS::Entity testEntity = createEntity();
        testEntity.addComponent(Components::TransformComponent(vec3<int>(5, 5, 0)));
        testEntity.addComponent(Components::AsciiRenderComponent(prop.get()));
        testEntity.addComponent(Components::EntityTagComponent("PlayerWASD"));
    }
    void onDeactivate() override {}
    void teardown() override {}
};

class Application : public AGE::CursesApplicationContext {
  public:
    Application(int width, int height) : AGE::CursesApplicationContext(width, height) {}
    ~Application() override = default;
    void init() override {
        CursesApplicationContext::init();
        using namespace AGE;

        Scene *scene = getSceneManager()->createScene<DefaultDrawScene>("Draw_Scene");

        using namespace AGE;
        // component registration
        scene->getRegistry()->registerComponent<Components::TransformComponent>();
        scene->getRegistry()->registerComponent<Components::AsciiRenderComponent>();
        scene->getRegistry()->registerComponent<Components::EntityTagComponent>();

        // ascii renderer setup and registration
        auto asciiRenderSystem = scene->getRegistry()->registerSystem<Systems::AsciiRenderSystem>(scene->getRegistry());
        asciiRenderSystem->setRenderer(asciiRenderer.get());
        auto asciiRenderSystemArchetype = asciiRenderSystem->getSystemArchetype();
        scene->getRegistry()->setSystemArchetype<Systems::AsciiRenderSystem>(asciiRenderSystemArchetype);

        // player wasd controller system setup and registation
        auto playerWASD = scene->getRegistry()->registerSystem<Systems::PlayerWASDControlSystem>(scene->getRegistry());
        auto playerWASDArchetype = playerWASD->getSystemArchetype();
        scene->getRegistry()->setSystemArchetype<Systems::PlayerWASDControlSystem>(playerWASDArchetype);

        getSceneManager()->setActiveScene("Draw_Scene");

        // render dispatch
        auto asciiRenderSystemPtr = asciiRenderSystem.get();
        std::unique_ptr<EventDispatcher>
            renderDispatcher =
            std::make_unique<FunctionEventDispatcher<Events::EngineDrawEvent>>(
                [asciiRenderSystemPtr](Events::EngineDrawEvent *event, EventQueue *queue) {
                  asciiRenderSystemPtr->render();
                });
        engineEventQueue->registerEventDispatcher<Events::EngineDrawEvent>(renderDispatcher.get());
        eventListeners["render"] = std::move(renderDispatcher);

        // keyboard dispatch
        auto playerWASDPtr = playerWASD.get();
        std::unique_ptr<EventDispatcher>
            keyboardDispatch =
            std::make_unique<FunctionEventDispatcher<Events::KeyPressedEvent>>(
                [playerWASDPtr](Events::KeyPressedEvent *event, EventQueue *queue) {
                  playerWASDPtr->move(event->getKeyCode());
                });
        applicationEventQueue->registerEventDispatcher<Events::KeyPressedEvent>(keyboardDispatch.get());
        eventListeners["player_wasd"] = std::move(keyboardDispatch);
    }

    void stop() override {
        CursesApplicationContext::stop();
        using namespace AGE;
        engineEventQueue->registerEventDispatcher<Events::EngineDrawEvent>(eventListeners["render"].get());
        applicationEventQueue->registerEventDispatcher<Events::KeyPressedEvent>(eventListeners["player_wasd"].get());
    }

};

// resolve entry point extern
std::unique_ptr<AGE::ApplicationContext> gameEntryPoint(int argc, char *argv[]) {
    return std::make_unique<Application>(80, 25);
}
