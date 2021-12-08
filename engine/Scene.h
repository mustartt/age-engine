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
    ECS::Registry registry;
  public:
    explicit Scene(std::string name = "Unknown Scene")
        : registry(), sceneName(std::move(name)) {}
    virtual ~Scene() = default;

    [[nodiscard]] const std::string &getSceneName() const { return sceneName; }

    ECS::Registry &getRegistry() { return registry; }
    ECS::Entity createEntity();
    void destroyEntity(const ECS::Entity &entity);

    virtual void setup() {};
    virtual void teardown() {};
};

}

#endif //FINAL_PROJECT_ENGINE_SCENE_H_
