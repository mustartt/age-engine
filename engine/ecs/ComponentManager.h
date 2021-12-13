//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_COMPONENTMANAGER_H_
#define FINAL_PROJECT_ENGINE_ECS_COMPONENTMANAGER_H_

#include "ecs.h"

#include <list>
#include <memory>

namespace AGE::ECS {

class ComponentAlreadyExist : public std::exception {};
class ComponentDoesNotExist : public std::exception {};
class ComponentNotRegistered : public std::exception {};
class ComponentAlreadyRegistered : public std::exception {};

class EntityDoesNotExist : public std::exception {};

class ComponentContainer {
  public:
    virtual ~ComponentContainer() = default;
    virtual void entityDestroyed(EntityID entity) = 0;
};

template<typename T>
class ConcreteComponentContainer : public ComponentContainer {
    using ListIter = typename std::list<T>::iterator;
    struct ListIterHash {
      size_t operator()(const ListIter &i) const {
          return std::hash<T *>()(&*i);
      }
    };
    std::list<T> components;
    std::unordered_map<EntityID, ListIter> entityComponentMapping;
    std::unordered_map<ListIter, EntityID, ListIterHash> componentEntityMapping;
  public:
    void insertEntityComponent(EntityID entity, T component) {
        if (entityComponentMapping.count(entity)) throw ComponentAlreadyExist{};
        ListIter iter = components.insert(components.end(), std::move(component));
        entityComponentMapping[entity] = iter;
        componentEntityMapping[iter] = entity;
    }
    void removeEntityComponent(EntityID entity) {
        if (!entityComponentMapping.count(entity)) throw EntityDoesNotExist{};
        auto iter = entityComponentMapping[entity];
        components.erase(iter);
        entityComponentMapping.erase(entity);
        componentEntityMapping.erase(iter);
    }
    T &getComponent(EntityID entity) {
        if (!entityComponentMapping.count(entity)) throw ComponentDoesNotExist{};
        return *entityComponentMapping[entity];
    }
    bool hasComponent(EntityID entity) {
        return entityComponentMapping.count(entity) > 0;
    }
    void entityDestroyed(EntityID entity) override {
        if (entityComponentMapping.count(entity)) {
            removeEntityComponent(entity);
        }
    }
};

class ComponentManager {
    std::unordered_map<ComponentType, ComponentID> componentTypes;
    std::unordered_map<ComponentType, std::unique_ptr<ComponentContainer>> componentArrays;
    ComponentID componentIDSequence = 0;
  public:
    template<typename T>
    void registerComponent() {
        if (componentTypes.count(typeid(T))) throw ComponentAlreadyRegistered{};
        componentTypes[typeid(T)] = componentIDSequence++;
        componentArrays[typeid(T)] = std::make_unique<ConcreteComponentContainer<T>>();
    }

    template<typename T>
    ComponentID getComponentType() {
        if (!componentTypes.count(typeid(T))) throw ComponentNotRegistered{};
        return componentTypes[typeid(T)];
    }

    template<typename T>
    bool hasComponent(EntityID entity) {
        if (!componentTypes.count(typeid(T))) throw ComponentNotRegistered{};
        auto container = static_cast<ConcreteComponentContainer<T> *>(componentArrays[typeid(T)].get());
        return container->hasComponent(entity);
    }

    template<typename T>
    void addComponent(EntityID entity, T component) {
        if (!componentTypes.count(typeid(T))) throw ComponentNotRegistered{};
        auto container = static_cast<ConcreteComponentContainer<T> *>(componentArrays[typeid(T)].get());
        container->insertEntityComponent(entity, component);
    }

    template<typename T>
    void removeComponent(EntityID entity) {
        if (!componentTypes.count(typeid(T))) throw ComponentNotRegistered{};
        auto container = static_cast<ConcreteComponentContainer<T> *>(componentArrays[typeid(T)].get());
        container->removeEntityComponent(entity);
    }

    template<typename T>
    T &getComponent(EntityID entity) {
        if (!componentTypes.count(typeid(T))) throw ComponentNotRegistered{};
        auto container = static_cast<ConcreteComponentContainer<T> *>(componentArrays[typeid(T)].get());
        return container->getComponent(entity);
    }

    void entityDestroyed(EntityID entity) {
        for (auto const &pair: componentArrays) {
            auto const &component = pair.second;
            component->entityDestroyed(entity);
        }
    }
};

}

#endif //FINAL_PROJECT_ENGINE_ECS_COMPONENTMANAGER_H_
