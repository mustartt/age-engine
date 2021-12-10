//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_OUTOFBOUND_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_OUTOFBOUND_H_

#include <utils/vec3.h>
#include <ecs/Registry.h>

namespace SpaceInvader::CustomCS {

class RemoveOnOutOfBoundComponent {
    AGE::vec3<int> top;
    AGE::vec3<int> bottom;
    int buffer;
  public:
    explicit RemoveOnOutOfBoundComponent(const AGE::vec3<int> &top,
                                         const AGE::vec3<int> &bottom,
                                         int buffer = 0);
    bool isOutOfBound(const AGE::vec3<int> &position);
  private:
    [[nodiscard]] bool outOfBound(int x1, int x2, int val) const;
};

class OutOfBoundSystem : public AGE::ECS::System {
  public:
    explicit OutOfBoundSystem(AGE::ECS::Registry *registry);
    void removeOutOfBoundEntities();
    AGE::ECS::Archetype getSystemArchetype() override;
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_OUTOFBOUND_H_
