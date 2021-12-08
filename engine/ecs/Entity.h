//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ENTITY_H_
#define FINAL_PROJECT_ENGINE_ENTITY_H_

#include "ecs.h"
#include "Registry.h"

namespace AGE::ECS {

class Entity {
    EntityID entityId;
    Registry *registry;
  public:
    explicit Entity(EntityID entityId, Registry *registry)
        : entityId{entityId}, registry{registry} {}
    Entity(const Entity &other) = default;
    Entity(Entity &&other) = default;
    Entity &operator=(const Entity &other) = default;

    [[nodiscard]] EntityID getEntityId() const { return entityId; }

    template<typename T>
    void addComponent(T component) { registry->addComponent(entityId, component); }
    template<typename T>
    bool hasComponent() { return registry->hasComponent<T>(entityId); }
    template<typename T>
    T &getComponent() { return registry->getComponent<T>(entityId); }
    template<typename T>
    void removeComponent() { registry->removeComponent<T>(entityId); }
};

}

#endif //FINAL_PROJECT_ENGINE_ENTITY_H_
