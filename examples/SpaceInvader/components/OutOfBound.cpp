//
// Created by henry on 2021-12-09.
//

#include "OutOfBound.h"
#include <ecs/Entity.h>
#include <components/Transform.h>

namespace SpaceInvader::CustomCS {

RemoveOnOutOfBoundComponent::RemoveOnOutOfBoundComponent(const AGE::vec3<int> &top,
                                                         const AGE::vec3<int> &bottom,
                                                         int buffer)
    : top(top), bottom(bottom), buffer(buffer) {}

bool RemoveOnOutOfBoundComponent::isOutOfBound(const AGE::vec3<int> &position) {
    return outOfBound(top.x, bottom.x, position.x)
        || outOfBound(top.y, bottom.y, position.y)
        || outOfBound(top.z, bottom.z, position.z);
}

bool RemoveOnOutOfBoundComponent::outOfBound(int x1, int x2, int val) const {
    return val < x1 - buffer || val >= x2 + buffer;
}

OutOfBoundSystem::OutOfBoundSystem(AGE::ECS::Registry *registry)
    : AGE::ECS::System(registry) {}

void OutOfBoundSystem::removeOutOfBoundEntities() {
    for (auto entityId: entities) {
        AGE::ECS::Entity entity(entityId, registry);
        if (!entity.isValid()) continue;
        auto &bound = entity.getComponent<RemoveOnOutOfBoundComponent>();
        auto &pos = entity.getComponent<AGE::Components::TransformComponent>();
        if (bound.isOutOfBound(pos.getPosition())) {
            entity.destroyEntity();
        }
    }
}

AGE::ECS::Archetype OutOfBoundSystem::getSystemArchetype() {
    AGE::ECS::Archetype archetype;
    archetype.push_back(registry->getComponentType<CustomCS::RemoveOnOutOfBoundComponent>());
    archetype.push_back(registry->getComponentType<AGE::Components::TransformComponent>());
    return archetype;
}

}
