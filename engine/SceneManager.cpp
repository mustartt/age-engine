//
// Created by henry on 2021-12-07.
//

#include "SceneManager.h"

namespace AGE {

std::optional<Scene *> SceneManager::getActiveScene() {
    return activeScene;
}

void SceneManager::setActiveScene(std::string &name) {
    if (!scenes.count(name)) throw UnknownSceneException{};
    activeScene = std::make_optional(scenes[name].get());
}

void SceneManager::unloadActiveScene() {
    activeScene = {};
}

template<typename SceneType, typename... Args>
void SceneManager::loadScene(std::string &name, Args &&... args) {
    scenes[name] = std::make_unique<SceneType>(std::forward<Args>(args)...);
}

}