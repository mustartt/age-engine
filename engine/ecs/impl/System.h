//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_SYSTEM_H_
#define FINAL_PROJECT_ENGINE_ECS_SYSTEM_H_

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <memory>


#include "../ecs.h"

namespace AGE {
namespace ECS {

class Registry;

class System {
  protected:
    Registry *registry;
  public:
    explicit System(Registry *registry) : registry(registry) {}
    std::set<EntityID> entities;
};

class SystemAlreadyRegistered : public std::exception {};
class SystemNotRegistered : public std::exception {};

class SystemManager {
    std::unordered_map<SystemType, Archetype> archetypes;
    std::unordered_map<SystemType, std::shared_ptr<System>> systems;
  public:
    template<typename T>
    std::shared_ptr<T> registerSystem(Registry *reg) {
        auto typeName = typeid(T).name();
        if (archetypes.count(typeName)) throw SystemAlreadyRegistered{};
        auto system = std::make_shared<T>(reg);
        systems[typeName] = system;
        return system;
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
}

#endif //FINAL_PROJECT_ENGINE_ECS_SYSTEM_H_
