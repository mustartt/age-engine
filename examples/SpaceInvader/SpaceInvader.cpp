//
// Created by henry on 2021-12-08.
//


#include <components/Transform.h>
#include <components/AsciiRender.h>
#include <components/EntityTag.h>
#include <components/BasicCollision.h>
#include <components/Health.h>
#include <components/OutOfBound.h>
#include <components/Player.h>
#include <components/Physics.h>
#include <renderer/RenderComponents/BitMapProp.h>
#include <utils/BitMapLoader.h>
#include <scenes/GameOverScene.h>
#include <renderer/RenderComponents/TextProp.h>
#include <components/MeteorSpawn.h>
#include <components/None.h>
#include <scenes/GameStartScene.h>
#include <components/PlayerScore.h>
#include "SpaceInvader.h"
#include "scenes/MainScene.h"
#include "components/SpaceInvaderComponentSystem.h"

namespace SpaceInvader {

void SpaceInvader::init() {
    CursesApplicationContext::init();
    using namespace AGE;

    resources["space"] = std::make_unique<Renderer::CharacterProp>(' ');
    resources["player"] = std::make_unique<Renderer::CharacterProp>('D');
    resources["bullet1"] = std::make_unique<Renderer::CharacterProp>('*');
    resources["bullet2"] = std::make_unique<Renderer::CharacterProp>('>');
    resources["meteor1"] = std::make_unique<Renderer::CharacterProp>('M');
    resources["meteor2"] = std::make_unique<Renderer::CharacterProp>('@');
    resources["game_over"] = std::make_unique<Renderer::BitMapProp>(
        BitMapLoader::loadBitMap("./assets/game_over.txt"));
    resources["game_start"] = std::make_unique<Renderer::BitMapProp>(
        BitMapLoader::loadBitMap("./assets/game_start.txt"));
    resources["default_border"] = std::make_unique<Renderer::BitMapProp>(
        BitMapLoader::loadBitMap("./assets/default_border.txt"));
    resources["game_over_text"] = std::make_unique<Renderer::TextProp>("Press Space to Exit...");
    resources["game_start_text"] = std::make_unique<Renderer::TextProp>("Press Space to Start...");
    resources["game_start_info"] = std::make_unique<Renderer::TextProp>("CTRL: WS to move up and down, JK to shoot!");
    resources["score_display"] = std::make_unique<Renderer::TextProp>("0");
    resources["health_display"] = std::make_unique<Renderer::TextProp>("10/10");
    resources["score_display_text"] = std::make_unique<Renderer::TextProp>("Score: ");
    resources["health_display_text"] = std::make_unique<Renderer::TextProp>("Health: ");

    Scene *mainScene = getSceneManager()->createScene<MainScene>("main_scene",
                                                                 engineEventQueue.get(),
                                                                 applicationEventQueue.get(),
                                                                 &resources);

    // component registration
    mainScene->getRegistry()->registerComponent<Components::None>();
    mainScene->getRegistry()->registerComponent<Components::TransformComponent>();
    mainScene->getRegistry()->registerComponent<Components::AsciiRenderComponent>();
    mainScene->getRegistry()->registerComponent<Components::EntityTagComponent>();
    mainScene->getRegistry()->registerComponent<Components::Velocity>();
    mainScene->getRegistry()->registerComponent<Health>();
    mainScene->getRegistry()->registerComponent<Components::BoundingBoxComponent>();
    mainScene->getRegistry()->registerComponent<CustomCS::RemoveOnOutOfBoundComponent>();
    mainScene->getRegistry()->registerComponent<PlayerScore>();

    // system registration
    // ascii renderer setup and registration
    auto asciiRenderSystem =
        mainScene->getRegistry()->registerSystem<Systems::AsciiRenderSystem>();
    asciiRenderSystem->setRenderer(asciiRenderer.get());
    auto asciiRenderSystemArchetype = asciiRenderSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<Systems::AsciiRenderSystem>(asciiRenderSystemArchetype);

    // player movement controller system setup and registation
    auto playerController =
        mainScene->getRegistry()->registerSystem<CustomCS::PlayerControlSystem>(&resources);
    auto playerControllerArchetype = playerController->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<CustomCS::PlayerControlSystem>(playerControllerArchetype);

    // meteor physics system
    auto physicsSystem =
        mainScene->getRegistry()->registerSystem<Systems::PhysicsSystem>();
    auto physicsSystemArchetype = physicsSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<Systems::PhysicsSystem>(physicsSystemArchetype);

    // basic collision system
    auto collisionSystem = mainScene->getRegistry()
        ->registerSystem<Systems::BasicCollisionSystem>(applicationEventQueue.get());
    auto collisionSystemArchetype = collisionSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<Systems::BasicCollisionSystem>(collisionSystemArchetype);

    // meteor collision handler system
    auto meteorCollisionSystem =
        mainScene->getRegistry()->registerSystem<CustomCS::MeteorBulletCollisionSystem>();
    auto meteorCollisionSystemArchetype = meteorCollisionSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<CustomCS::MeteorBulletCollisionSystem>(meteorCollisionSystemArchetype);

    // out of bound system
    auto outOfBoundSystem =
        mainScene->getRegistry()->registerSystem<CustomCS::OutOfBoundSystem>();
    auto outOfBoundSystemArchetype = outOfBoundSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<CustomCS::OutOfBoundSystem>(outOfBoundSystemArchetype);

    // meteor spawning system
    auto meteorSpawnSystem =
        mainScene->getRegistry()->registerSystem<CustomCS::MeteorSpawnSystem>(&resources);
    auto meteorSpawnSystemArchetype = meteorSpawnSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<CustomCS::MeteorSpawnSystem>(meteorSpawnSystemArchetype);

    // player score
    auto playerSystem = mainScene->getRegistry()->registerSystem<PlayerScoreSystem>();
    auto scoreSystemArchetype = playerSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<PlayerScoreSystem>(scoreSystemArchetype);

    // player health
    auto healthSystem = mainScene->getRegistry()->registerSystem<PlayerHealthSystem>();
    auto healthSystemArchetype = healthSystem->getSystemArchetype();
    mainScene->getRegistry()->setSystemArchetype<PlayerHealthSystem>(healthSystemArchetype);

    mainScene->setup();

    Scene *gameStartScene = getSceneManager()->createScene<GameStartScene>("game_start_scene",
                                                                           engineEventQueue.get(),
                                                                           applicationEventQueue.get(),
                                                                           &resources);

    // register game over scene components
    gameStartScene->getRegistry()->registerComponent<Components::AsciiRenderComponent>();
    gameStartScene->getRegistry()->registerComponent<Components::TransformComponent>();
    gameStartScene->getRegistry()->registerComponent<Components::EntityTagComponent>();

    // ascii renderer setup and registration
    auto asciiRenderSystem3 =
        gameStartScene->getRegistry()->registerSystem<Systems::AsciiRenderSystem>();
    asciiRenderSystem3->setRenderer(asciiRenderer.get());
    auto asciiRenderSystem3Archetype = asciiRenderSystem3->getSystemArchetype();
    gameStartScene->getRegistry()->setSystemArchetype<Systems::AsciiRenderSystem>(asciiRenderSystem3Archetype);

    gameStartScene->setup();

    Scene *gameOverScene = getSceneManager()->createScene<GameOverScene>("game_over_scene",
                                                                         engineEventQueue.get(),
                                                                         applicationEventQueue.get(),
                                                                         &resources);

    // register game over scene components
    gameOverScene->getRegistry()->registerComponent<Components::AsciiRenderComponent>();
    gameOverScene->getRegistry()->registerComponent<Components::TransformComponent>();
    gameOverScene->getRegistry()->registerComponent<Components::EntityTagComponent>();

    // ascii renderer setup and registration
    auto asciiRenderSystem2 =
        gameOverScene->getRegistry()->registerSystem<Systems::AsciiRenderSystem>();
    asciiRenderSystem2->setRenderer(asciiRenderer.get());
    auto asciiRenderSystem2Archetype = asciiRenderSystem->getSystemArchetype();
    gameOverScene->getRegistry()->setSystemArchetype<Systems::AsciiRenderSystem>(asciiRenderSystem2Archetype);

    gameOverScene->setup();

    getSceneManager()->setActiveScene("game_start_scene");
}

void SpaceInvader::stop() {
    CursesApplicationContext::stop();
}

}
