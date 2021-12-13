//
// Created by henry on 2021-12-12.
//

#include "Movement.h"

namespace FeatureDemo {

void CyclicMovementSystem::move() {
    for (auto entityId: entities) {
        auto entity = ECS::Entity(entityId, registry);
        auto &transform = entity.getComponent<Components::TransformComponent>();
        auto &movement = entity.getComponent<CyclicMovement>();
        movement.performMovement(transform);
    }
}

ECS::Archetype CyclicMovementSystem::getSystemArchetype() {
    AGE::ECS::Archetype archetype;
    archetype.push_back(registry->getComponentType<Components::TransformComponent>());
    archetype.push_back(registry->getComponentType<CyclicMovement>());
    return archetype;
}

CyclicMovementSystem::CyclicMovementSystem(ECS::Registry *registry) : ECS::System(registry) {}

CyclicMovement::CyclicMovement(std::vector<Movement> modes) : modes(std::move(modes)), index(0) {}

void CyclicMovement::performMovement(Components::TransformComponent &transform) {
    modes[index](transform);
    increment();
}

void CyclicMovement::increment() { index = (index + 1) % (int)modes.size(); }

}
