//
// Created by henry on 2021-12-09.
//

#include <components/AsciiRender.h>
#include <components/Transform.h>
#include <components/EntityTag.h>
#include "GameOverScene.h"

namespace SpaceInvader {

GameOverScene::GameOverScene(const std::string &name,
                             EventQueue *engine,
                             EventQueue *application,
                             ResourceManager *resources)
    : Scene(name),
      engineEventQueue(engine),
      applicationEventQueue(application),
      resources{resources} {}

void GameOverScene::init() {

}

void GameOverScene::setup() {
    using namespace AGE;
    auto gameover = createEntity();
    gameover.addComponent(Components::AsciiRenderComponent(resources->at("game_over").get()));
    gameover.addComponent(Components::TransformComponent(vec3<int>(13, 5, 0)));
    gameover.addComponent(Components::EntityTagComponent("game_over_text"));

    auto border = createEntity();
    border.addComponent(Components::AsciiRenderComponent(resources->at("default_border").get()));
    border.addComponent(Components::TransformComponent(vec3<int>(0, 0, 100)));
    border.addComponent(Components::EntityTagComponent("default_border"));
}

void GameOverScene::onActivate() {
    using namespace AGE;
    // render dispatch
    auto asciiRenderSystem = getRegistry()->getRegisteredSystem<Systems::AsciiRenderSystem>();
    std::unique_ptr<EventDispatcher>
        renderDispatcher =
        std::make_unique<FunctionEventDispatcher<Events::EngineDrawEvent>>(
            [=](Events::EngineDrawEvent *event, EventQueue *queue) {
              asciiRenderSystem->render();
            });
    engineEventQueue->registerEventDispatcher<Events::EngineDrawEvent>(renderDispatcher.get());
    eventListeners["render"] = std::move(renderDispatcher);

    std::unique_ptr<EventDispatcher>
        keyboardDispatch =
        std::make_unique<FunctionEventDispatcher<Events::KeyPressedEvent>>(
            [this](Events::KeyPressedEvent *event, EventQueue *queue) {
              if (event->getKeyCode() == ' ') {
                  engineEventQueue->enqueue<Events::EngineShutdownEvent>();
              }
            });
    applicationEventQueue->registerEventDispatcher<Events::KeyPressedEvent>(keyboardDispatch.get());
    eventListeners["keyboard"] = std::move(keyboardDispatch);
}

void GameOverScene::onDeactivate() {
    engineEventQueue->unregisterAll<Events::EngineDrawEvent>();
    applicationEventQueue->unregisterAll<Events::KeyPressedEvent>();
}

void GameOverScene::teardown() {

}

}