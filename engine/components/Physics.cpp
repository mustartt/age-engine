//
// Created by henry on 2021-12-09.
//

#include <components/Transform.h>
#include "Physics.h"

namespace AGE::Systems {

void PhysicsSystem::update() {
    for (auto entityId: entities) {
        auto entity = AGE::ECS::Entity(entityId, registry);
        if (!entity.isValid()) return;
        auto &position = entity.getComponent<Components::TransformComponent>();
        auto &velocity = entity.getComponent<Components::Velocity>();
        position.getPosition() += velocity.getVelocity();
    }
}

AGE::ECS::Archetype PhysicsSystem::getSystemArchetype() {
    using namespace AGE;
    ECS::Archetype archetype;
    archetype.push_back(registry->getComponentType<Components::TransformComponent>());
    archetype.push_back(registry->getComponentType<Components::Velocity>());
    return archetype;
}

}
