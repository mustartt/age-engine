//
// Created by henry on 2021-12-08.
//

#ifndef FINAL_PROJECT_ENGINE_COMPONENTS_BASICCOLLISION_H_
#define FINAL_PROJECT_ENGINE_COMPONENTS_BASICCOLLISION_H_

#include <ecs/SystemManager.h>
#include <utils/vec2.h>
#include <utils/vec3.h>

namespace AGE::Components {

class BoundingBoxComponent {
    vec2<int> boundingBox;
    vec2<int> offset;
  public:
    explicit BoundingBoxComponent(const vec2<int> &box, const vec2<int> &offset = {0, 0})
        : boundingBox(box), offset(offset) {}
    [[nodiscard]] const vec2<int> &getBoundingBox() const { return boundingBox; }
    [[nodiscard]] const vec2<int> &getOffset() const { return offset; }
};

}

namespace AGE {

class EventQueue;

namespace Systems {

class BasicCollisionSystem : public ECS::System {
    /* uses TransformComponent, BoundingBoxComponent */
    EventQueue *targetEventQueue;
  public:
    explicit BasicCollisionSystem(ECS::Registry *registry, EventQueue *eventQueue)
        : ECS::System(registry), targetEventQueue(eventQueue) {}
    void detectCollisions();
    ECS::Archetype getSystemArchetype() override;
  private:
    static bool collisionCheck(const Components::BoundingBoxComponent &a, const vec3<int> &posA,
                               const Components::BoundingBoxComponent &b, const vec3<int> &posB);
};
}
}

#endif //FINAL_PROJECT_ENGINE_COMPONENTS_BASICCOLLISION_H_
