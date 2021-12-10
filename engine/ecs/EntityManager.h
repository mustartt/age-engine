//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_ENTITYMANAGER_H_
#define FINAL_PROJECT_ENGINE_ECS_ENTITYMANAGER_H_

#include "ecs.h"

#include <unordered_map>

namespace AGE::ECS {

class InvalidEntityException : public std::exception {};

class EntityManager {
    std::unordered_map<EntityID, Archetype> entityComponentMapping;
    EntityID entitySequenceID;
    size_t entityCount;
    // id generator singleton

  public:
    EntityManager() : entitySequenceID{0}, entityCount{0},
                      entityComponentMapping{} {}
    ~EntityManager() = default;

    EntityID createEntity() {
        ++entityCount;
        return entitySequenceID++;
    }
    void destroyEntity(EntityID entity) {
        if (!entityComponentMapping.count(entity)) throw InvalidEntityException();
        entityComponentMapping.erase(entity);
        --entityCount;
    }
    void setArchetype(EntityID entity, Archetype &archetype) {
        entityComponentMapping[entity] = archetype;
    }
    Archetype &getArchetype(EntityID entity) {
        return entityComponentMapping[entity];
    }
};

}

#endif //FINAL_PROJECT_ENGINE_ECS_ENTITYMANAGER_H_
