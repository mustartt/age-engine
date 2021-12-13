//
// Created by henry on 2021-12-12.
//

#include <components/AsciiRender.h>
#include <components/Movement.h>
#include <components/Physics.h>
#include "MovementScene.h"

namespace FeatureDemo {

void MovementScene::init() {

}

void MovementScene::setup() {
    using namespace AGE;
    auto straightEntity = createEntity();
    straightEntity.addComponent(Components::TransformComponent(vec3<int>(5, 5, 0)));
    straightEntity.addComponent(Components::AsciiRenderComponent(resources->at("char_prop").get()));
    straightEntity.addComponent(Components::Velocity(vec3<int>(1, 0, 0)));

    auto stationaryEntity = createEntity();
    stationaryEntity.addComponent(Components::TransformComponent(vec3<int>(5, 10, 0)));
    stationaryEntity.addComponent(Components::AsciiRenderComponent(resources->at("char_prop").get()));
    stationaryEntity.addComponent(CyclicMovement(
        std::vector<std::function<void(Components::TransformComponent &)>>
            ({
                 [](Components::TransformComponent &transform) {
                   transform.getPosition().x += 2;
                 },
                 [](Components::TransformComponent &transform) {
                   transform.getPosition().y += 2;
                 },
                 [](Components::TransformComponent &transform) {
                   transform.getPosition().x -= 2;
                 },
                 [](Components::TransformComponent &transform) {
                   transform.getPosition().y -= 2;
                 }
             })
    ));
    auto notStraightEntity = createEntity();
    notStraightEntity.addComponent(Components::TransformComponent(vec3<int>(5, 15, 0)));
    notStraightEntity.addComponent(Components::AsciiRenderComponent(resources->at("char_prop").get()));
    notStraightEntity.addComponent(CyclicMovement(
        std::vector<std::function<void(Components::TransformComponent &)>>
            ({
                 [](Components::TransformComponent &transform) {
                   transform.getPosition().x += 2;
                 },
                 [](Components::TransformComponent &transform) {
                   transform.getPosition().y += 2;
                 },
                 [](Components::TransformComponent &transform) {
                   transform.getPosition().x -= 2;
                 },
                 [](Components::TransformComponent &transform) {
                   transform.getPosition().y -= 2;
                 }
             })
    ));
    notStraightEntity.addComponent(Components::Velocity(vec3<int>(1, 0, 0)));
}

void MovementScene::onActivate() {
    using namespace AGE;
    auto asciiRenderSystemPtr = getRegistry()->getRegisteredSystem<Systems::AsciiRenderSystem>();
    std::unique_ptr<EventDispatcher>
        renderDispatcher =
        std::make_unique<FunctionEventDispatcher<Events::EngineDrawEvent>>(
            [asciiRenderSystemPtr](Events::EngineDrawEvent *event, EventQueue *queue) {
              asciiRenderSystemPtr->render();
            });
    engineEventQueue->registerEventDispatcher<Events::EngineDrawEvent>(renderDispatcher.get());
    eventListeners["render"] = std::move(renderDispatcher);

    auto physicsSystem = getRegistry()->getRegisteredSystem<Systems::PhysicsSystem>();
    auto movementSystem = getRegistry()->getRegisteredSystem<CyclicMovementSystem>();
    std::unique_ptr<EventDispatcher>
        engineUpdateHandler =
        std::make_unique<FunctionEventDispatcher<Events::EngineUpdateEvent>>(
            [=](Events::EngineUpdateEvent *event, EventQueue *queue) {
              physicsSystem->update();
              movementSystem->move();
            });
    engineEventQueue->registerEventDispatcher<Events::EngineUpdateEvent>(engineUpdateHandler.get());
    eventListeners["update"] = std::move(engineUpdateHandler);
}

void MovementScene::onDeactivate() {
    engineEventQueue->unregisterAll<Events::EngineDrawEvent>();
    engineEventQueue->unregisterAll<Events::EngineUpdateEvent>();
}

void MovementScene::teardown() {

}

}


