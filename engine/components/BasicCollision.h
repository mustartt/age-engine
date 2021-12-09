//
// Created by henry on 2021-12-08.
//

#ifndef FINAL_PROJECT_ENGINE_COMPONENTS_BASICCOLLISION_H_
#define FINAL_PROJECT_ENGINE_COMPONENTS_BASICCOLLISION_H_

#include <ecs/SystemManager.h>
#include <ecs/Entity.h>
#include <events/Event.h>
#include <events/engine_events/EngineEvent.h>
#include "utils/vec2.h"
#include "utils/vec3.h"
#include "EngineComponents.h"

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

namespace AGE::Systems {

class BasicCollisionSystem : public ECS::System {
    /* uses TransformComponent, BoundingBoxComponent */
    EventQueue *targetEventQueue;
  public:
    explicit BasicCollisionSystem(ECS::Registry *registry, EventQueue *eventQueue)
        : ECS::System(registry), targetEventQueue(eventQueue) {}
    void detectCollisions() {
        std::vector<ECS::EntityID> collidingEntities(entities.begin(), entities.end());
        for (int i = 0; i < collidingEntities.size() - 1; ++i) {
            for (int j = i + 1; j < collidingEntities.size(); ++j) {
                auto entityA = collidingEntities[i];
                auto entityB = collidingEntities[j];
                if (entityA == entityB) continue;

                auto testA = ECS::Entity(entityA, registry);
                auto &transformA = testA.getComponent<Components::TransformComponent>();
                auto &bBoxA = testA.getComponent<Components::BoundingBoxComponent>();

                auto testB = ECS::Entity(entityB, registry);
                auto &transformB = testB.getComponent<Components::TransformComponent>();
                auto &bBoxB = testB.getComponent<Components::BoundingBoxComponent>();

                if (collisionCheck(bBoxA, transformA.getPosition(), bBoxB, transformB.getPosition())) {
                    targetEventQueue->enqueue<Events::BasicCollisionEvent>(testA, testB);
                }
            }
        }
    }
    ECS::Archetype getSystemArchetype() override {
        using namespace AGE;
        ECS::Archetype archetype;
        archetype.push_back(registry->getComponentType<Components::TransformComponent>());
        archetype.push_back(registry->getComponentType<Components::BoundingBoxComponent>());
        return archetype;
    }
  private:
    static bool collisionCheck(const Components::BoundingBoxComponent &a, const vec3<int> &posA,
                               const Components::BoundingBoxComponent &b, const vec3<int> &posB) {
        if (posA.z != posB.z) return false;
        vec2<int> offA = {posA.x + a.getBoundingBox().x, posA.y + a.getBoundingBox().y};
        vec2<int> offB = {posB.x + b.getBoundingBox().x, posB.y + b.getBoundingBox().y};
        if (offA.x < offB.x + b.getBoundingBox().x &&
            offB.x < offA.x + a.getBoundingBox().x &&
            offA.y < offB.y + b.getBoundingBox().y &&
            offB.y < offA.y + a.getBoundingBox().y) {
            return true;
        }
        return false;
    }
};

}

#endif //FINAL_PROJECT_ENGINE_COMPONENTS_BASICCOLLISION_H_
