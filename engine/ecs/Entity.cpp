//
// Created by henry on 2021-12-01.
//

#include "Entity.h"

namespace AGE {
namespace ECS {

EntityManager::EntityManager()
    : entitySequenceID{0}, entityCount{0},
      entityComponentMapping{} {}

EntityID EntityManager::createEntity() {
    ++entityCount;
    return ++entitySequenceID;
}

void EntityManager::destroyEntity(EntityID &entity) {
    if (!entityComponentMapping.count(entity)) throw InvalidEntityException();
    entityComponentMapping.erase(entity);
    --entityCount;
}

void EntityManager::setArchetype(EntityID &entity, Archetype &archetype) {
    entityComponentMapping[entity] = archetype;
}

Archetype &EntityManager::getArchetype(EntityID &entity) {
    if (!entityComponentMapping.count(entity)) throw InvalidEntityException();
    return entityComponentMapping[entity];
}

}
}