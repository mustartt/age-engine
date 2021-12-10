//
// Created by henry on 2021-12-09.
//

#include "BasicCollision.h"
#include "Transform.h"

#include <vector>
#include <ecs/Entity.h>
#include <events/Event.h>
#include <events/EngineEvents/EngineEvents.h>

namespace AGE::Systems {

void BasicCollisionSystem::detectCollisions() {
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

ECS::Archetype BasicCollisionSystem::getSystemArchetype() {
    using namespace AGE;
    ECS::Archetype archetype;
    archetype.push_back(registry->getComponentType<Components::TransformComponent>());
    archetype.push_back(registry->getComponentType<Components::BoundingBoxComponent>());
    return archetype;
}

bool BasicCollisionSystem::collisionCheck(const Components::BoundingBoxComponent &a,
                                          const vec3<int> &posA,
                                          const Components::BoundingBoxComponent &b,
                                          const vec3<int> &posB) {
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

}
