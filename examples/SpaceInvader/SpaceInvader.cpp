//
// Created by henry on 2021-12-08.
//


#include <components/Transform.h>
#include <components/AsciiRender.h>
#include <components/EntityTag.h>
#include <components/BasicCollision.h>
#include "SpaceInvader.h"
#include "scenes/MainScene.h"
#include "components/SpaceInvaderComponentSystem.h"

namespace SpaceInvader {

void SpaceInvader::init() {
    CursesApplicationContext::init();
    using namespace AGE;

    resources["player"] = std::make_unique<Renderer::CharacterProp>('A');
    resources["bullet1"] = std::make_unique<Renderer::CharacterProp>('*');
    resources["bullet2"] = std::make_unique<Renderer::CharacterProp>('^');
    resources["bullet3"] = std::make_unique<Renderer::CharacterProp>('v');
    resources["meteor1"] = std::make_unique<Renderer::CharacterProp>('M');
    resources["meteor2"] = std::make_unique<Renderer::CharacterProp>('@');

    Scene *mainScene = getSceneManager()->createScene<MainScene>("main_scene",
                                                                 engineEventQueue.get(),
                                                                 applicationEventQueue.get(),
                                                                 &resources);

    // component registration
    mainScene->getRegistry()->registerComponent<Components::TransformComponent>();
    mainScene->getRegistry()->registerComponent<Components::AsciiRenderComponent>();
    mainScene->getRegistry()->registerComponent<Components::EntityTagComponent>();
    mainScene->getRegistry()->registerComponent<CustomCS::Velocity>();
    mainScene->getRegistry()->registerComponent<CustomCS::Health>();
    mainScene->getRegistry()->registerComponent<Components::BoundingBoxComponent>();
    mainScene->getRegistry()->registerComponent<CustomCS::RemoveOnOutOfBoundComponent>();

    // system registration
    // ascii renderer setup and registration
    auto asciiRenderSystem =
        mainScene->getRegistry()->registerSystem<Systems::AsciiRenderSystem>(mainScene->getRegistry());
    asciiRenderSystem->setRenderer(asciiRenderer.get());
    auto asciiRenderSystemArchetype = asciiRenderSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<Systems::AsciiRenderSystem>(asciiRenderSystemArchetype);

    // player movement controller system setup and registation
    auto playerController =
        mainScene->getRegistry()->registerSystem<CustomCS::PlayerControlSystem>(mainScene->getRegistry(), &resources);
    auto playerControllerArchetype = playerController->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<CustomCS::PlayerControlSystem>(playerControllerArchetype);

    // meteor physics system
    auto physicsSystem =
        mainScene->getRegistry()->registerSystem<CustomCS::PhysicsSystem>(mainScene->getRegistry());
    auto physicsSystemArchetype = physicsSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<CustomCS::PhysicsSystem>(physicsSystemArchetype);

    // basic collision system
    auto collisionSystem = mainScene->getRegistry()
        ->registerSystem<Systems::BasicCollisionSystem>(mainScene->getRegistry(), applicationEventQueue.get());
    auto collisionSystemArchetype = collisionSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<Systems::BasicCollisionSystem>(collisionSystemArchetype);

    // meteor collision handler system
    auto meteorCollisionSystem =
        mainScene->getRegistry()->registerSystem<CustomCS::MeteorBulletCollisionSystem>(mainScene->getRegistry());
    auto meteorCollisionSystemArchetype = meteorCollisionSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<CustomCS::MeteorBulletCollisionSystem>(meteorCollisionSystemArchetype);

    // out of bound system
    auto outOfBoundSystem =
        mainScene->getRegistry()->registerSystem<CustomCS::OutOfBoundSystem>(mainScene->getRegistry());
    auto outOfBoundSystemArchetype = outOfBoundSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<CustomCS::OutOfBoundSystem>(outOfBoundSystemArchetype);

    mainScene->setup();
    getSceneManager()->setActiveScene("main_scene");
}

void SpaceInvader::stop() {
    CursesApplicationContext::stop();
}

}
