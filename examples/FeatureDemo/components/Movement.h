//
// Created by henry on 2021-12-12.
//

#ifndef FINAL_PROJECT_EXAMPLES_FEATUREDEMO_COMPONENTS_MOVEMENT_H_
#define FINAL_PROJECT_EXAMPLES_FEATUREDEMO_COMPONENTS_MOVEMENT_H_

#include <utils/vec3.h>
#include <vector>
#include <functional>
#include <components/Transform.h>
#include <ecs/Entity.h>

namespace FeatureDemo {

using namespace AGE;

using Movement = std::function<void(Components::TransformComponent &)>;

class CyclicMovement {
    int index;
    std::vector<Movement> modes;
  public:
    explicit CyclicMovement(std::vector<Movement> modes);
    void performMovement(Components::TransformComponent &transform);
  private:
    void increment();
};

class CyclicMovementSystem : public ECS::System {
  public:
    explicit CyclicMovementSystem(ECS::Registry *registry);
    void move();
    ECS::Archetype getSystemArchetype() override;
};

}

#endif //FINAL_PROJECT_EXAMPLES_FEATUREDEMO_COMPONENTS_MOVEMENT_H_
