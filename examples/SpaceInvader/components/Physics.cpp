//
// Created by henry on 2021-12-09.
//

#include <components/Transform.h>
#include "Physics.h"
#include "Velocity.h"

namespace SpaceInvader::CustomCS {

PhysicsSystem::PhysicsSystem(AGE::ECS::Registry *registry) : AGE::ECS::System(registry) {}

void PhysicsSystem::update() {
    for (auto entityId: entities) {
        auto entity = AGE::ECS::Entity(entityId, registry);
        auto &position = entity.getComponent<AGE::Components::TransformComponent>();
        auto &velocity = entity.getComponent<CustomCS::Velocity>();
        position.getPosition() += velocity.getVelocity();
    }
}

AGE::ECS::Archetype PhysicsSystem::getSystemArchetype() {
    using namespace AGE;
    ECS::Archetype archetype;
    archetype.push_back(registry->getComponentType<Components::TransformComponent>());
    archetype.push_back(registry->getComponentType<CustomCS::Velocity>());
    return archetype;
}

}