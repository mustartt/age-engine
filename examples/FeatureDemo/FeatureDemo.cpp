//
// Created by henry on 2021-12-12.
//

#include <renderer/RenderComponents/CharacterProp.h>
#include <renderer/RenderComponents/RectProp.h>
#include <renderer/RenderComponents/BitMapProp.h>
#include <utils/BitMapLoader.h>
#include <renderer/RenderComponents/TextProp.h>
#include <renderer/RenderComponents/CyclicRenderProp.h>
#include <components/Transform.h>
#include <components/AsciiRender.h>
#include <components/EntityTag.h>
#include <scenes/IntroScene.h>
#include <components/BasicPlayerMovement.h>
#include <components/Movement.h>
#include <scenes/MovementScene.h>
#include "FeatureDemo.h"
#include "components/Physics.h"

namespace FeatureDemo {

void FeatureDemo::init() {
    CursesApplicationContext::init();
    using namespace AGE;

    resources["char_prop"] = std::make_unique<Renderer::CharacterProp>('C');
    resources["rect_prop"] = std::make_unique<Renderer::RectProp>('#', 5, 5);
    resources["scene_1_message"] = std::make_unique<Renderer::TextProp>("Different Render Components");
    resources["bitmap_prop"] =
        std::make_unique<Renderer::BitMapProp>(
            BitMapLoader::loadBitMap("./assets/example_bitmap.txt"));
    resources["progress_cycle_1"] =
        std::make_unique<Renderer::BitMapProp>(BitMapLoader::loadBitMap("./assets/progress_cycle_1.txt"));
    resources["progress_cycle_2"] =
        std::make_unique<Renderer::BitMapProp>(BitMapLoader::loadBitMap("./assets/progress_cycle_2.txt"));
    resources["progress_cycle_3"] =
        std::make_unique<Renderer::BitMapProp>(BitMapLoader::loadBitMap("./assets/progress_cycle_3.txt"));
    resources["progress_cycle_4"] =
        std::make_unique<Renderer::BitMapProp>(BitMapLoader::loadBitMap("./assets/progress_cycle_4.txt"));
    resources["cyclic_prop"] = std::make_unique<Renderer::CyclicRenderProp>
        (std::vector<Renderer::AsciiRenderProp *>(
            {
                resources["progress_cycle_1"].get(),
                resources["progress_cycle_2"].get(),
                resources["progress_cycle_3"].get(),
                resources["progress_cycle_4"].get()
            }
        ));

    Scene *intro = getSceneManager()->createScene<IntroScene>("scene_1",
                                                              engineEventQueue.get(),
                                                              applicationEventQueue.get(),
                                                              &resources);
    // component registration
    intro->getRegistry()->registerComponent<Components::TransformComponent>();
    intro->getRegistry()->registerComponent<Components::AsciiRenderComponent>();
    intro->getRegistry()->registerComponent<Components::EntityTagComponent>();

    // system registration
    auto asciiRenderSystem = intro->getRegistry()->registerSystem<Systems::AsciiRenderSystem>();
    asciiRenderSystem->setRenderer(asciiRenderer.get());
    auto asciiRenderSystemArchetype = asciiRenderSystem->getSystemArchetype();
    intro->getRegistry()->setSystemArchetype<Systems::AsciiRenderSystem>(asciiRenderSystemArchetype);

    auto wasdSystem = intro->getRegistry()->registerSystem<Systems::PlayerWASDControlSystem>();
    auto wasdSystemArchetype = wasdSystem->getSystemArchetype();
    intro->getRegistry()->setSystemArchetype<Systems::PlayerWASDControlSystem>(wasdSystemArchetype);

    intro->setup();

    Scene *movement = getSceneManager()->createScene<MovementScene>("scene_2",
                                                                    engineEventQueue.get(),
                                                                    applicationEventQueue.get(),
                                                                    &resources);
    // component registration
    movement->getRegistry()->registerComponent<Components::TransformComponent>();
    movement->getRegistry()->registerComponent<Components::AsciiRenderComponent>();
    movement->getRegistry()->registerComponent<Components::EntityTagComponent>();
    movement->getRegistry()->registerComponent<CyclicMovement>();
    movement->getRegistry()->registerComponent<Components::Velocity>();

    // system registration
    auto asciiRenderSystem2 = movement->getRegistry()->registerSystem<Systems::AsciiRenderSystem>();
    asciiRenderSystem2->setRenderer(asciiRenderer.get());
    auto asciiRenderSystem2Archetype = asciiRenderSystem2->getSystemArchetype();
    intro->getRegistry()->setSystemArchetype<Systems::AsciiRenderSystem>(asciiRenderSystem2Archetype);

    auto cyclicSystem = movement->getRegistry()->registerSystem<CyclicMovementSystem>();
    auto cyclicSystemArchetype = cyclicSystem->getSystemArchetype();
    movement->getRegistry()->setSystemArchetype<CyclicMovementSystem>(cyclicSystemArchetype);

    auto physicsSystem = movement->getRegistry()->registerSystem<Systems::PhysicsSystem>();
    auto physicsSystemArchetype = physicsSystem->getSystemArchetype();
    movement->getRegistry()->setSystemArchetype<Systems::PhysicsSystem>(physicsSystemArchetype);

    movement->setup();

    getSceneManager()->setActiveScene("scene_2");
}

void FeatureDemo::stop() {
    CursesApplicationContext::stop();
}

}
