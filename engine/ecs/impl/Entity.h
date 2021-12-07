//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ENTITY_H_
#define FINAL_PROJECT_ENGINE_ENTITY_H_

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

#include "../ecs.h"

namespace AGE::ECS {

class EntityManager {
    std::unordered_map<EntityID, Archetype> entityComponentMapping;
    EntityID entitySequenceID;
    size_t entityCount;
    // id generator singleton

  public:
    EntityManager();
    ~EntityManager() = default;

    EntityID createEntity();
    void destroyEntity(EntityID entity);
    void setArchetype(EntityID entity, Archetype &archetype);
    Archetype &getArchetype(EntityID entity);
};

class InvalidEntityException : public std::exception {};

EntityManager::EntityManager()
    : entitySequenceID{0}, entityCount{0},
      entityComponentMapping{} {}

EntityID EntityManager::createEntity() {
    ++entityCount;
    return entitySequenceID++;
}

void EntityManager::destroyEntity(EntityID entity) {
    if (!entityComponentMapping.count(entity)) throw InvalidEntityException();
    entityComponentMapping.erase(entity);
    --entityCount;
}

void EntityManager::setArchetype(EntityID entity, Archetype &archetype) {
    entityComponentMapping[entity] = archetype;
}

Archetype &EntityManager::getArchetype(EntityID entity) {
    return entityComponentMapping[entity];
}

}

#endif //FINAL_PROJECT_ENGINE_ENTITY_H_
