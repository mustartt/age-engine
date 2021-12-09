//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_REGISTRY_H_

#include "ecs.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace AGE::ECS {

class Registry {
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<ComponentManager> componentManager;
    std::unique_ptr<SystemManager> systemManager;
  public:
    Registry() : entityManager(std::make_unique<EntityManager>()),
                 componentManager(std::make_unique<ComponentManager>()),
                 systemManager(std::make_unique<SystemManager>()) {};
    ~Registry() = default;

    EntityID createEntity() {
        return entityManager->createEntity();
    }

    void destroyEntity(EntityID entityId) {
        entityManager->destroyEntity(entityId);
        componentManager->entityDestroyed(entityId);
        systemManager->entityDestroyed(entityId);
    }

    template<typename T>
    void addComponent(EntityID entity, T component) {
        componentManager->addComponent<T>(entity, component);
        auto &archetype = entityManager->getArchetype(entity);
        archetype.push_back(componentManager->template getComponentType<T>());
        systemManager->entitySignatureChanged(entity, archetype);
    }

    template<typename T>
    void removeComponent(EntityID entity) {
        componentManager->removeComponent<T>(entity);
        std::vector<ComponentID> archetype = entityManager->getArchetype(entity);
        std::remove(archetype.begin(), archetype.end(), componentManager->getComponentType<T>());
        systemManager->entitySignatureChanged(entity, archetype);
    }

    template<typename T>
    bool hasComponent(EntityID entity) {
        return componentManager->hasComponent<T>(entity);
    }

    template<typename T>
    T &getComponent(EntityID entity) {
        return componentManager->getComponent<T>(entity);
    }

    template<typename T>
    ComponentID getComponentType() {
        return componentManager->getComponentType<T>();
    }

    template<typename T>
    void registerComponent() {
        componentManager->template registerComponent<T>();
    }

    template<typename T>
    std::shared_ptr<T> registerSystem(Registry *reg) {
        return systemManager->template registerSystem<T>(reg);
    }

    template<typename T>
    T *getRegisteredSystem() {
        return systemManager->template getRegisteredSystem<T>();
    }

    template<typename T>
    void setSystemArchetype(Archetype &archetype) {
        systemManager->template setArchetype<T>(archetype);
    }
};

}

#define FINAL_PROJECT_ENGINE_ECS_REGISTRY_H_

#endif //FINAL_PROJECT_ENGINE_ECS_REGISTRY_H_
