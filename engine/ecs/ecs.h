//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_ECS_H_
#define FINAL_PROJECT_ENGINE_ECS_ECS_H_

#include "../age.h"
#include "impl/Entity.h"
#include "impl/Component.h"
#include "impl/System.h"
#include "impl/Registry.h"

namespace AGE::ECS {

using EntityID = std::uint64_t;
using ComponentID = EntityID;
using Archetype = std::vector<ComponentID>;
using ComponentType = const char *;
using SystemType = const char *;

class Entity {
    EntityID entityId;
    Registry *registry;
  public:
    explicit Entity(EntityID entityId, Registry *registry)
        : entityId{entityId}, registry{registry} {}
    Entity(Entity &other) = default;
    Entity(Entity &&other) = default;
    Entity &operator=(const Entity &other) = default;

};

}

#endif //FINAL_PROJECT_ENGINE_ECS_ECS_H_
