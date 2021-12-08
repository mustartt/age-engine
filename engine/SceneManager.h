//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_SCENEMANAGER_H_
#define FINAL_PROJECT_ENGINE_SCENEMANAGER_H_

#include <unordered_map>
#include <memory>
#include <exception>
#include "Scene.h"

namespace AGE {

class UnknownSceneException : public std::exception {};

class SceneManager final {
    std::optional<Scene *> activeScene;
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
  public:
    SceneManager() = default;
    ~SceneManager() = default;

    std::optional<Scene *> getActiveScene();
    void setActiveScene(std::string &name);
    void unloadActiveScene();
    template<typename SceneType, typename... Args>
    void loadScene(std::string &name, Args &&... args);
};

}

#endif //FINAL_PROJECT_ENGINE_SCENEMANAGER_H_
