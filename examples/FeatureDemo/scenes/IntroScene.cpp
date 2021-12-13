//
// Created by henry on 2021-12-12.
//

#include <components/Transform.h>
#include <components/AsciiRender.h>
#include <components/EntityTag.h>
#include <components/BasicPlayerMovement.h>
#include "IntroScene.h"

namespace FeatureDemo {

void IntroScene::init() {

}

void IntroScene::setup() {
    using namespace AGE;
    auto charEntity = createEntity();
    charEntity.addComponent(Components::TransformComponent(vec3(3, 3, 0)));
    charEntity.addComponent(Components::AsciiRenderComponent(resources->at("char_prop").get()));

    auto rectEntity = createEntity();
    rectEntity.addComponent(Components::TransformComponent(vec3(7, 3, 0)));
    rectEntity.addComponent(Components::AsciiRenderComponent(resources->at("rect_prop").get()));

    auto bitmapEntity = createEntity();
    bitmapEntity.addComponent(Components::TransformComponent(vec3(15, 2, 0)));
    bitmapEntity.addComponent(Components::AsciiRenderComponent(resources->at("bitmap_prop").get()));

    auto player = createEntity();
    player.addComponent(Components::TransformComponent(vec3(3, 15, 0)));
    player.addComponent(Components::AsciiRenderComponent(resources->at("cyclic_prop").get()));
    player.addComponent(Components::EntityTagComponent("PlayerWASD"));

}

void IntroScene::onActivate() {
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

    auto playerControl = getRegistry()->getRegisteredSystem<Systems::PlayerWASDControlSystem>();
    std::unique_ptr<EventDispatcher>
        keyboardDispatch =
        std::make_unique<FunctionEventDispatcher<Events::KeyPressedEvent>>(
            [playerControl](Events::KeyPressedEvent *event, EventQueue *queue) {
              playerControl->move(event->getKeyCode());
            });
    applicationEventQueue->registerEventDispatcher<Events::KeyPressedEvent>(keyboardDispatch.get());
    eventListeners["keyboard"] = std::move(keyboardDispatch);
}

void IntroScene::onDeactivate() {
    using namespace AGE;
    engineEventQueue->unregisterAll<Events::EngineDrawEvent>();
    engineEventQueue->unregisterAll<Events::EngineUpdateEvent>();
    applicationEventQueue->unregisterAll<Events::KeyPressedEvent>();
}

void IntroScene::teardown() {

}

}
