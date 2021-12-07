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

class Entity {
    EntityID entityId;
    Registry *registry;
  public:
    explicit Entity(EntityID entityId, Registry *registry)
        : entityId{entityId}, registry{registry} {}
    Entity(Entity &other) = default;
    Entity(Entity &&other) = default;
    Entity &operator=(const Entity &other) = default;

    template<typename T>
    void addComponent(T component) { registry->addComponent(entityId, component); }
    template<typename T>
    bool hasComponent() { registry->hasComponent<T>(entityId); }
    template<typename T>
    T &getComponent() { registry->getComponent<T>(entityId); }
    template<typename T>
    void removeComponent() { registry->removeComponent<T>(entityId); }
};

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
