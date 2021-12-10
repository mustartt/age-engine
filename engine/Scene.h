//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_SCENE_H_
#define FINAL_PROJECT_ENGINE_SCENE_H_

#include "age.h"
#include "ecs/Entity.h"

namespace AGE {

class Scene {
    std::string sceneName;
    std::unique_ptr<ECS::Registry> registry;
  public:
    explicit Scene(std::string name = "Unnamed Scene")
        : registry(std::make_unique<ECS::Registry>()),
          sceneName(std::move(name)) {}
    virtual ~Scene() = default;

    [[nodiscard]] const std::string &getSceneName() const { return sceneName; }

    ECS::Registry *getRegistry() { return registry.get(); }
    ECS::Entity createEntity() {
        auto id = registry->createEntity();
        return ECS::Entity(id, registry.get());
    }
    void destroyEntity(const ECS::Entity &entity) {
        registry->destroyEntity(entity.getEntityId());
    }

    virtual void init() {};
    virtual void setup() {}; // must be explicitly called by the user
    virtual void onActivate() {};
    virtual void onDeactivate() {};
    virtual void teardown() {};
};

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
            loadedScenes.at(activeSceneName.value())->onDeactivate();
        }
        activeSceneName = name;
        loadedScenes[name]->onActivate();
    }
};

}

#endif //FINAL_PROJECT_ENGINE_SCENE_H_
