//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_ECS_H_
#define FINAL_PROJECT_ENGINE_ECS_ECS_H_

#include <cstdint>
#include <vector>
#include <memory>

namespace AGE {
namespace ECS {

using EntityID = std::uint64_t;
using ComponentID = EntityID;
using Archetype = std::vector<ComponentID>;
using ComponentType = const char *;
using SystemType = const char *;

class Registry {
    using EntityType = EntityID;
  public:
    Registry() = default;
    virtual ~Registry() = default;

    virtual EntityType createEntity() = 0;
    virtual void destroyEntity(EntityType entityId) = 0;

};

class Entity {
    EntityID entityId;
    Registry *registry;
  public:
    Entity() = default;
    Entity(EntityID entityId, Registry *registry)
        : entityId{entityId}, registry{registry} {}
    Entity(const Entity &other) = default;
};

}
}

#endif //FINAL_PROJECT_ENGINE_ECS_ECS_H_
