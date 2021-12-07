//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_REGISTRY_H_

#include <vector>
#include "../ecs.h"
#include "Entity.h"
#include "Component.h"
#include "System.h"

namespace AGE {
namespace ECS {

class BasicRegistry : public Registry {
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<ComponentManager> componentManager;
    std::unique_ptr<SystemManager> systemManager;
  public:
    BasicRegistry() : entityManager(std::make_unique<EntityManager>()),
                      componentManager(std::make_unique<ComponentManager>()),
                      systemManager(std::make_unique<SystemManager>()) {};
    ~BasicRegistry() override = default;

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
    std::shared_ptr<T> registerSystem(BasicRegistry *reg) {
        return systemManager->template registerSystem<T>(reg);
    }
    template<typename T>
    void setSystemArchetype(Archetype &archetype) {
        systemManager->template setArchetype<T>(archetype);
    }
};

}
}

#define FINAL_PROJECT_ENGINE_ECS_REGISTRY_H_

#endif //FINAL_PROJECT_ENGINE_ECS_REGISTRY_H_
