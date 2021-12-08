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
    virtual void onActivate() {};
    virtual void onDeactivate() {};
    virtual void teardown() {};
};

}

#endif //FINAL_PROJECT_ENGINE_SCENE_H_
