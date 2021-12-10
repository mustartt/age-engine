//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_SYSTEMMANAGER_H_
#define FINAL_PROJECT_ENGINE_ECS_SYSTEMMANAGER_H_

#include "ecs.h"

#include <set>
#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <typeindex>

namespace AGE::ECS {

class Registry;

class System {
  protected:
    Registry *registry;
  public:
    std::set<EntityID> entities;
    explicit System(Registry *registry) : registry(registry) {}
    virtual ~System() = default;
    virtual Archetype getSystemArchetype() = 0;
};

class SystemAlreadyRegistered : public std::exception {};
class SystemNotRegistered : public std::exception {};

class SystemManager {
    std::unordered_map<SystemType, Archetype> archetypes;
    std::unordered_map<SystemType, std::unique_ptr<System>> systems;
  public:
    template<typename T, typename... Args>
    T *registerSystem(Registry *reg, Args &&... args) {
        auto typeName = typeid(T).name();
        if (archetypes.count(typeName)) throw SystemAlreadyRegistered{};
        systems[typeName] = std::move(std::make_unique<T>(reg, args...));
        return static_cast<T *>(systems[typeName].get());
    }

    template<typename T>
    T *getRegisteredSystem() {
        auto typeName = typeid(T).name();
        if (!systems.count(typeName)) throw SystemNotRegistered{};
        return static_cast<T *>(systems[typeName].get());
    }

    template<typename T>
    void setArchetype(Archetype &signature) {
        auto typeName = typeid(T).name();
        if (!systems.count(typeName)) throw SystemNotRegistered{};
        archetypes[typeName] = signature;
    }

    void entityDestroyed(EntityID entity) {
        for (auto const &pair: systems) {
            auto const &system = pair.second;
            system->entities.erase(entity);
        }
    }

    void entitySignatureChanged(EntityID entity, Archetype &entityArchetype) {
        for (auto const &pair: systems) {
            auto const &type = pair.first;
            auto const &system = pair.second;
            auto const &systemArchetype = archetypes[type];

            if (hasRequiredArchetype(entityArchetype, systemArchetype)) {
                system->entities.insert(entity);
            } else {
                system->entities.erase(entity);
            }
        }
    }
  private:
    static bool hasRequiredArchetype(const Archetype &test, const Archetype &parent) {
        return std::all_of(parent.begin(), parent.end(), [test](auto id) {
          return std::find(test.begin(), test.end(), id) != test.end();
        });
    }
};

}

#endif //FINAL_PROJECT_ENGINE_ECS_SYSTEMMANAGER_H_
