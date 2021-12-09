//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_SCENEMANAGER_H_
#define FINAL_PROJECT_ENGINE_SCENEMANAGER_H_

#include <string>
#include <optional>
#include <unordered_map>
#include <memory>
#include <exception>

#include "Scene.h"

namespace AGE {

class InvalidSceneName : public std::exception {};

class SceneManager {
    std::optional<std::string> activeSceneName;
    std::unordered_map<std::string, std::unique_ptr<Scene>> loadedScenes;
  public:
    SceneManager() = default;
    ~SceneManager() {
        for (auto &pair: loadedScenes) {
            pair.second->onDeactivate();
            pair.second->teardown();
        }
    };

    template<class SceneType, typename ...Args>
    Scene *createScene(const std::string &name = "Unnamed Scene", Args &&...args) {
        if (loadedScenes.count(name)) throw InvalidSceneName{};
        loadedScenes[name] = std::make_unique<SceneType>(name, args...);
        loadedScenes[name]->init();
        return loadedScenes[name].get();
    }

    void unloadScene(const std::string &name) {
        if (!loadedScenes.count(name)) throw InvalidSceneName{};
        loadedScenes[name]->teardown();
        loadedScenes.erase(name);
    }

    std::optional<Scene *> getActiveScene() {
        if (!activeSceneName) return {};
        return std::make_optional(loadedScenes[activeSceneName.value()].get());
    }

    void setActiveScene(const std::string &name) {
        if (!loadedScenes.count(name)) throw InvalidSceneName{};
        if (activeSceneName) {
            loadedScenes[activeSceneName.value()]->onDeactivate();
        }
        activeSceneName = name;
        loadedScenes[name]->onActivate();
    }
};

}

#endif //FINAL_PROJECT_ENGINE_SCENEMANAGER_H_
