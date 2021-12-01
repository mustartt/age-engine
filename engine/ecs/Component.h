//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_COMPONENT_H_
#define FINAL_PROJECT_ENGINE_ECS_COMPONENT_H_

#include <typeinfo>
#include "ecs.h"
#include "Entity.h"

namespace AGE {
namespace ECS {

class Component {
    Registry *registry;
  protected:
    template<typename T>
    T &GetComponent(Entity &entity);
};

class ComponentManager {
  public:
    template<typename T>
    void registerComponent();
    template<typename T>
    ComponentType getComponentID();
    template<typename T>
    void addComponent(Entity &entity, T Component);
    template<typename T>
    void removeComponent(Entity &entity);
    template<typename T>
    T &getComponent(Entity &entity);
    void entityDestoryed(Entity &entity);
};

}
}

#endif //FINAL_PROJECT_ENGINE_ECS_COMPONENT_H_
