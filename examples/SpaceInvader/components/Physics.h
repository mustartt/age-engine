//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_PHYSICS_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_PHYSICS_H_

#include <ecs/Entity.h>

namespace SpaceInvader::CustomCS {

class PhysicsSystem : public AGE::ECS::System {
    /* uses TransformComponent, Velocity */
  public:
    explicit PhysicsSystem(AGE::ECS::Registry *registry);
    ~PhysicsSystem() = default;
    void update();
    AGE::ECS::Archetype getSystemArchetype() override;
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_PHYSICS_H_
