//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_PHYSICS_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_PHYSICS_H_

#include <ecs/Entity.h>

namespace AGE::Components {

class Velocity {
    AGE::vec3<int> velocity;
  public:
    explicit Velocity(const AGE::vec3<int> &velocity) : velocity(velocity) {}
    [[nodiscard]] const AGE::vec3<int> &getVelocity() const { return velocity; }
};

}

namespace AGE::Systems {

class PhysicsSystem : public AGE::ECS::System {
    /* uses TransformComponent, Velocity */
  public:
    explicit PhysicsSystem(AGE::ECS::Registry *registry) : AGE::ECS::System(registry) {}
    ~PhysicsSystem() override = default;
    void update();
    AGE::ECS::Archetype getSystemArchetype() override;
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_PHYSICS_H_
