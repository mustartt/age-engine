//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ENTITY_H_
#define FINAL_PROJECT_ENGINE_ENTITY_H_

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

#include "ecs.h"

namespace AGE {
namespace ECS {

class EntityManager {
    std::unordered_map<EntityID, Archetype> entityComponentMapping;
    EntityID entitySequenceID;
    size_t entityCount;
    // id generator singleton

  public:
    EntityManager();
    ~EntityManager() = default;

    EntityID createEntity();
    void destroyEntity(EntityID &entity);
    void setArchetype(EntityID &entity, Archetype &archetype);
    Archetype &getArchetype(EntityID &entity);
};

class InvalidEntityException : public std::exception {};

}
}

#endif //FINAL_PROJECT_ENGINE_ENTITY_H_
