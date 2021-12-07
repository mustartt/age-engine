//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_COMPONENT_H_
#define FINAL_PROJECT_ENGINE_ECS_COMPONENT_H_

#include "../ecs.h"

namespace AGE::ECS {

//class Component {
//    Registry *registry;
//  protected:
//    template<typename T>
//    T &GetComponent(EntityID &entity);
//};

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
    void entityDestroyed(EntityID entity) override {
        if (entityComponentMapping.count(entity)) {
            removeEntityComponent(entity);
        }
    }
};

class ComponentManager {
    std::unordered_map<ComponentType, ComponentID> componentTypes;
    std::unordered_map<ComponentType, std::shared_ptr<ComponentContainer>> componentArrays;
    ComponentID componentIDSequence = 0;
  public:
    template<typename T>
    void registerComponent() {
        auto typeName = typeid(T).name();
        if (componentTypes.count(typeName)) throw ComponentAlreadyRegistered{};
        componentTypes[typeName] = componentIDSequence++;
        componentArrays[typeName] = std::make_shared<ConcreteComponentContainer<T>>();
    }

    template<typename T>
    ComponentID getComponentType() {
        auto typeName = typeid(T).name();
        if (!componentTypes.count(typeName)) throw ComponentNotRegistered{};
        return componentTypes[typeName];
    }

    template<typename T>
    void addComponent(EntityID entity, T component) {
        getComponentArray<T>()->insertEntityComponent(entity, component);
    }

    template<typename T>
    void removeComponent(EntityID entity) {
        getComponentArray<T>()->removeEntityComponent(entity);
    }

    template<typename T>
    T &getComponent(EntityID entity) {
        return getComponentArray<T>()->getComponent(entity);
    }

    void entityDestroyed(EntityID entity) {
        for (auto const &pair: componentArrays) {
            auto const &component = pair.second;
            component->entityDestroyed(entity);
        }
    }

  private:
    template<typename T>
    std::shared_ptr<ConcreteComponentContainer<T>> getComponentArray() {
        auto typeName = typeid(T).name();
        if (!componentTypes.count(typeName)) throw ComponentNotRegistered{};
        return std::static_pointer_cast<ConcreteComponentContainer<T>>(componentArrays[typeName]);
    }
};

}

#endif //FINAL_PROJECT_ENGINE_ECS_COMPONENT_H_
