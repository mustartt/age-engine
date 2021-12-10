//
// Created by henry on 2021-12-08.
//

#include <utils/vec3.h>
#include <components/BasicCollision.h>
#include <components/EntityTag.h>
#include <components/AsciiRender.h>
#include <components/Transform.h>
#include <components/Velocity.h>
#include <components/Physics.h>
#include <components/OutOfBound.h>
#include <components/Player.h>
#include "MainScene.h"
#include "../components/SpaceInvaderComponentSystem.h"

namespace SpaceInvader {

void MainScene::init() {

}

void MainScene::setup() {
    AGE::ECS::Entity player = createEntity();
    player.addComponent(AGE::Components::TransformComponent(vec3<int>(40, 20, 0)));
    player.addComponent(AGE::Components::AsciiRenderComponent(resources->at("player").get()));
    player.addComponent(AGE::Components::EntityTagComponent("Player"));

    for (int x = 0; x < 3; ++x) {
        for (int i = 0; i < 10; ++i) {
            AGE::ECS::Entity meteor1 = createEntity();
            meteor1.addComponent(AGE::Components::TransformComponent(vec3<int>(35 + i, 10 - x, 0)));
            meteor1.addComponent(AGE::Components::AsciiRenderComponent(resources->at("meteor2").get()));
            meteor1.addComponent(AGE::Components::EntityTagComponent("meteor"));
            meteor1.addComponent(CustomCS::Velocity(vec3<int>(0, 0, 0)));
            meteor1.addComponent(AGE::Components::BoundingBoxComponent(vec2<int>(1, 1)));
        }
    }
}

void MainScene::onActivate() {
    using namespace AGE;
    // render dispatch
    auto asciiRenderSystemPtr = getRegistry()->getRegisteredSystem<Systems::AsciiRenderSystem>();
    std::unique_ptr<EventDispatcher>
        renderDispatcher =
        std::make_unique<FunctionEventDispatcher<Events::EngineDrawEvent>>(
            [asciiRenderSystemPtr](Events::EngineDrawEvent *event, EventQueue *queue) {
              asciiRenderSystemPtr->render();
            });
    engineEventQueue->registerEventDispatcher<Events::EngineDrawEvent>(renderDispatcher.get());
    eventListeners["render"] = std::move(renderDispatcher);

    // physics update dispatch
    auto physicsSystem = getRegistry()->getRegisteredSystem<CustomCS::PhysicsSystem>();
    // collision update dispatch
    auto collisionSystem = getRegistry()->getRegisteredSystem<Systems::BasicCollisionSystem>();
    // out of bound dispatch
    auto outOfBoundSystem = getRegistry()->getRegisteredSystem<CustomCS::OutOfBoundSystem>();
    std::unique_ptr<EventDispatcher>
        engineUpdateHandler =
        std::make_unique<FunctionEventDispatcher<Events::EngineUpdateEvent>>(
            [=](Events::EngineUpdateEvent *event, EventQueue *queue) {
              physicsSystem->update();
              outOfBoundSystem->removeOutOfBoundEntities();
              collisionSystem->detectCollisions();
            });
    engineEventQueue->registerEventDispatcher<Events::EngineUpdateEvent>(engineUpdateHandler.get());
    eventListeners["physics"] = std::move(engineUpdateHandler);

    // keyboard dispatch
    auto playerControl = getRegistry()->getRegisteredSystem<CustomCS::PlayerControlSystem>();
    std::unique_ptr<EventDispatcher>
        keyboardDispatch =
        std::make_unique<FunctionEventDispatcher<Events::KeyPressedEvent>>(
            [playerControl](Events::KeyPressedEvent *event, EventQueue *queue) {
              playerControl->move(event->getKeyCode());
            });
    applicationEventQueue->registerEventDispatcher<Events::KeyPressedEvent>(keyboardDispatch.get());
    eventListeners["player"] = std::move(keyboardDispatch);

    auto meteorCollisionSystem = getRegistry()->getRegisteredSystem<CustomCS::MeteorBulletCollisionSystem>();
    // collision event dispatch
    std::unique_ptr<EventDispatcher>
        collisionDispatch =
        std::make_unique<FunctionEventDispatcher<Events::BasicCollisionEvent>>(
            [meteorCollisionSystem](Events::BasicCollisionEvent *event, EventQueue *queue) {
              meteorCollisionSystem->handleCollisions(event, queue);
            });
    applicationEventQueue->registerEventDispatcher<Events::BasicCollisionEvent>(collisionDispatch.get());
    eventListeners["collision"] = std::move(collisionDispatch);
}

void MainScene::onDeactivate() {
    using namespace AGE;
    engineEventQueue->unregisterEventDispatcher<Events::EngineDrawEvent>(eventListeners["render"].get());
    engineEventQueue->unregisterEventDispatcher<Events::EngineUpdateEvent>(eventListeners["physics"].get());
    applicationEventQueue->unregisterEventDispatcher<Events::KeyPressedEvent>(eventListeners["player"].get());
    applicationEventQueue->unregisterEventDispatcher<Events::BasicCollisionEvent>(eventListeners["collision"].get());
}

void MainScene::teardown() {

}

}
