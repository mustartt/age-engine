//
// Created by henry on 2021-12-08.
//

#include <utils/vec3.h>
#include <components/BasicCollision.h>
#include <components/EntityTag.h>
#include <components/AsciiRender.h>
#include <components/Transform.h>
#include <components/Physics.h>
#include <components/OutOfBound.h>
#include <components/Player.h>
#include <components/MeteorSpawn.h>
#include <components/PlayerScore.h>
#include <events/MeteorPastBorder.h>
#include <components/Health.h>
#include "MainScene.h"
#include "../components/SpaceInvaderComponentSystem.h"

namespace SpaceInvader {

void MainScene::init() {

}

void MainScene::setup() {
    AGE::ECS::Entity player = createEntity();
    player.addComponent(AGE::Components::TransformComponent(vec3<int>(5, 9, 0)));
    player.addComponent(AGE::Components::AsciiRenderComponent(resources->at("player").get()));
    player.addComponent(AGE::Components::EntityTagComponent("Player"));

    auto border = createEntity();
    border.addComponent(Components::AsciiRenderComponent(resources->at("default_border").get()));
    border.addComponent(Components::TransformComponent(vec3<int>(0, 0, 100)));
    border.addComponent(Components::EntityTagComponent("default_border"));

    auto score = createEntity();
    score.addComponent(Components::TransformComponent(vec3<int>(9, 23, 100)));
    score.addComponent(Components::AsciiRenderComponent(resources->at("score_display").get()));
    score.addComponent(Components::EntityTagComponent("score_display"));
    score.addComponent(PlayerScore());

    auto scoreText = createEntity();
    scoreText.addComponent(Components::TransformComponent(vec3<int>(0, 23, 100)));
    scoreText.addComponent(Components::AsciiRenderComponent(resources->at("score_display_text").get()));
    scoreText.addComponent(Components::EntityTagComponent("score_display"));

    auto health = createEntity();
    health.addComponent(Components::TransformComponent(vec3<int>(9, 22, 100)));
    health.addComponent(Components::AsciiRenderComponent(resources->at("health_display").get()));
    health.addComponent(Components::EntityTagComponent("health_display"));
    health.addComponent(Health(10, 10));

    auto healthText = createEntity();
    healthText.addComponent(Components::TransformComponent(vec3<int>(0, 22, 100)));
    healthText.addComponent(Components::AsciiRenderComponent(resources->at("health_display_text").get()));
    healthText.addComponent(Components::EntityTagComponent("health_display"));

    AGE::ECS::Entity meteor1 = createEntity();
    meteor1.addComponent(AGE::Components::TransformComponent(vec3<int>(5, 5, -100)));
    meteor1.addComponent(AGE::Components::AsciiRenderComponent(resources->at("space").get()));
    meteor1.addComponent(AGE::Components::EntityTagComponent("meteor"));
    meteor1.addComponent(AGE::Components::Velocity(vec3<int>(0, 0, 0)));
    meteor1.addComponent(AGE::Components::BoundingBoxComponent(vec2<int>(1, 1)));

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
    auto physicsSystem = getRegistry()->getRegisteredSystem<Systems::PhysicsSystem>();
    // collision update dispatch
    auto collisionSystem = getRegistry()->getRegisteredSystem<Systems::BasicCollisionSystem>();
    // out of bound dispatch
    auto outOfBoundSystem = getRegistry()->getRegisteredSystem<CustomCS::OutOfBoundSystem>();
    // meteor spawn
    auto meteorSpawnSystem = getRegistry()->getRegisteredSystem<CustomCS::MeteorSpawnSystem>();

    std::unique_ptr<EventDispatcher>
        engineUpdateHandler =
        std::make_unique<FunctionEventDispatcher<Events::EngineUpdateEvent>>(
            [=](Events::EngineUpdateEvent *event, EventQueue *queue) {
              meteorSpawnSystem->spawn();
              physicsSystem->update();
              outOfBoundSystem->removeOutOfBoundEntities(queue);
              collisionSystem->detectCollisions();
            });
    engineEventQueue->registerEventDispatcher<Events::EngineUpdateEvent>(engineUpdateHandler.get());
    eventListeners["update"] = std::move(engineUpdateHandler);

    // keyboard dispatch
    auto playerControl = getRegistry()->getRegisteredSystem<CustomCS::PlayerControlSystem>();
    std::unique_ptr<EventDispatcher>
        keyboardDispatch =
        std::make_unique<FunctionEventDispatcher<Events::KeyPressedEvent>>(
            [playerControl](Events::KeyPressedEvent *event, EventQueue *queue) {
              playerControl->move(event->getKeyCode());
              if (event->getKeyCode() == 'p') {
                  queue->enqueue<Events::SwitchSceneEvent>("game_over_scene");
              }
            });
    applicationEventQueue->registerEventDispatcher<Events::KeyPressedEvent>(keyboardDispatch.get());
    eventListeners["keyboard"] = std::move(keyboardDispatch);

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

    auto playerScoreSystem = getRegistry()->getRegisteredSystem<PlayerScoreSystem>();
    std::unique_ptr<EventDispatcher>
        scoreDispatch =
        std::make_unique<FunctionEventDispatcher<ScoreEvent>>(
            [=](ScoreEvent *event, EventQueue *queue) {
              playerScoreSystem->playerScoreHandler();
            });
    applicationEventQueue->registerEventDispatcher<ScoreEvent>(scoreDispatch.get());
    eventListeners["score"] = std::move(scoreDispatch);

    auto healthSystem = getRegistry()->getRegisteredSystem<PlayerHealthSystem>();
    auto const appQueue = applicationEventQueue;
    std::unique_ptr<EventDispatcher>
        healthDispatch =
        std::make_unique<FunctionEventDispatcher<MeteorPastBorderEvent>>(
            [=](MeteorPastBorderEvent *event, EventQueue *queue) {
              healthSystem->handleOutOfBound(appQueue);
            });
    engineEventQueue->registerEventDispatcher<MeteorPastBorderEvent>(healthDispatch.get());
    eventListeners["health"] = std::move(healthDispatch);
}

void MainScene::onDeactivate() {
    using namespace AGE;

    engineEventQueue->unregisterAll<Events::EngineDrawEvent>();
    engineEventQueue->unregisterAll<Events::EngineUpdateEvent>();
    applicationEventQueue->unregisterAll<Events::KeyPressedEvent>();
    applicationEventQueue->unregisterAll<Events::BasicCollisionEvent>();
    applicationEventQueue->unregisterAll<ScoreEvent>();
    engineEventQueue->unregisterAll<MeteorPastBorderEvent>();

//    engineEventQueue->unregisterEventDispatcher<Events::EngineDrawEvent>(eventListeners.at("render").get());
//    engineEventQueue->unregisterEventDispatcher<Events::EngineUpdateEvent>(eventListeners.at("update").get());
//    applicationEventQueue->unregisterEventDispatcher<Events::KeyPressedEvent>(eventListeners.at("keyboard").get());
//    applicationEventQueue->unregisterEventDispatcher<Events::BasicCollisionEvent>(eventListeners.at("collision").get());
}

void MainScene::teardown() {

}

}
