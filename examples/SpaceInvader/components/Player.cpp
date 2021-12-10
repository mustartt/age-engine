//
// Created by henry on 2021-12-09.
//

#include "Player.h"

#include <ecs/Entity.h>
#include <utils/vec2.h>
#include <utils/vec3.h>
#include <components/Transform.h>
#include <components/AsciiRender.h>
#include <components/BasicCollision.h>
#include <components/EntityTag.h>
#include "Velocity.h"
#include "OutOfBound.h"

namespace SpaceInvader::CustomCS {

PlayerControlSystem::PlayerControlSystem(AGE::ECS::Registry *registry, ResourceManager *manager)
    : AGE::ECS::System(registry),
      resourceManager(manager) {}

void PlayerControlSystem::fireProjectile(ProjectileType type, const AGE::vec3<int> &pos) {
    auto bullet = AGE::ECS::Entity(registry->createEntity(), registry);
    auto *bulletProp = resourceManager->at("bullet2").get();
    auto bulletPosition = AGE::vec3<int>(pos) + AGE::vec3<int>(0, -1, 0);
    bullet.addComponent(AGE::Components::TransformComponent(bulletPosition));
    bullet.addComponent(AGE::Components::AsciiRenderComponent(bulletProp));
    bullet.addComponent(CustomCS::Velocity(AGE::vec3<int>(0, -1, 0)));
    bullet.addComponent(AGE::Components::EntityTagComponent("bullet"));
    bullet.addComponent(AGE::Components::BoundingBoxComponent(AGE::vec2<int>(1, 1)));
    bullet.addComponent(CustomCS::RemoveOnOutOfBoundComponent(
        AGE::vec3<int>(0, 5, -100),
        AGE::vec3<int>(80, 25, 100)));
}

void PlayerControlSystem::move(int keycode) {
    for (auto &entityId: entities) {
        auto entity = AGE::ECS::Entity(entityId, registry);
        auto &tag = entity.getComponent<AGE::Components::EntityTagComponent>();
        if (tag.getTag() == "Player") {
            auto &transform = entity.getComponent<AGE::Components::TransformComponent>();
            switch (keycode) {
                case 'w':fireProjectile(REGULAR, transform.getPosition());
                    break;
                case 'a':transform.getPosition().x -= 1;
                    break;
                case 'd':transform.getPosition().x += 1;
                    break;
                default:break;
            }
        }
    }
}

AGE::ECS::Archetype PlayerControlSystem::getSystemArchetype() {
    using namespace AGE;
    AGE::ECS::Archetype archetype;
    archetype.push_back(registry->getComponentType<Components::TransformComponent>());
    archetype.push_back(registry->getComponentType<Components::EntityTagComponent>());
    return archetype;
}

}