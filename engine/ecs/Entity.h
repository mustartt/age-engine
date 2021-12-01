//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ENTITY_H_
#define FINAL_PROJECT_ENGINE_ENTITY_H_

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

#include "ecs.h"

namespace AGE {
namespace ECS {

class Entity {
    EntityID id;
    std::string entityName;
    std::string entityTag;
  public:
    Entity();
    ~Entity();
  private:
    EntityID getID() const { return id; }
    const std::string &getEntityName() const { return entityName; }
    const std::string &getEntityTag() const { return entityTag; }
};

class EntityManager {
    std::unordered_map<EntityID, Archtype> entityComponentMapping;
    size_t entityCount;
    // id generator singleton
  public:
    Entity createEntity();
    void destoryEntity();
    void setArchtype(Entity &entity);
    Archtype &getArchtype(Entity &entity);
};

}
}

#endif //FINAL_PROJECT_ENGINE_ENTITY_H_
