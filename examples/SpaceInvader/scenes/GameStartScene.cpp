//
// Created by henry on 2021-12-12.
//

#include <components/AsciiRender.h>
#include <components/Transform.h>
#include <components/EntityTag.h>
#include "GameStartScene.h"

namespace SpaceInvader {

GameStartScene::GameStartScene(const std::string &name,
                               EventQueue *engine,
                               EventQueue *application,
                               ResourceManager *resources)
    : Scene(name),
      engineEventQueue(engine),
      applicationEventQueue(application),
      resources{resources} {}

void GameStartScene::init() {

}

void GameStartScene::setup() {
    using namespace AGE;
    auto gameover = createEntity();
    gameover.addComponent(Components::AsciiRenderComponent(resources->at("game_start").get()));
    gameover.addComponent(Components::TransformComponent(vec3<int>(3, 0, 0)));
    gameover.addComponent(Components::EntityTagComponent("game_start_text"));

    auto text = createEntity();
    text.addComponent(Components::AsciiRenderComponent(resources->at("game_start_text").get()));
    text.addComponent(Components::TransformComponent(vec3<int>(27, 19, 50)));
    text.addComponent(Components::EntityTagComponent("game_start_text"));

    auto info = createEntity();
    info.addComponent(Components::AsciiRenderComponent(resources->at("game_start_info").get()));
    info.addComponent(Components::TransformComponent(vec3<int>(19, 18, 50)));
    info.addComponent(Components::EntityTagComponent("game_start_info"));

    auto border = createEntity();
    border.addComponent(Components::AsciiRenderComponent(resources->at("default_border").get()));
    border.addComponent(Components::TransformComponent(vec3<int>(0, 0, 100)));
    border.addComponent(Components::EntityTagComponent("default_border"));
}

void GameStartScene::onActivate() {
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
                  applicationEventQueue->enqueue<Events::SwitchSceneEvent>("main_scene");
              }
            });
    applicationEventQueue->registerEventDispatcher<Events::KeyPressedEvent>(keyboardDispatch.get());
    eventListeners["keyboard"] = std::move(keyboardDispatch);
}

void GameStartScene::onDeactivate() {
    engineEventQueue->unregisterAll<Events::EngineDrawEvent>();
    applicationEventQueue->unregisterAll<Events::KeyPressedEvent>();
}

void GameStartScene::teardown() {

}

}
