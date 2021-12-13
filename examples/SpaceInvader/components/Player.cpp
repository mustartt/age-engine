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
#include <components/Physics.h>
#include "OutOfBound.h"

namespace SpaceInvader::CustomCS {

PlayerControlSystem::PlayerControlSystem(AGE::ECS::Registry *registry, ResourceManager *manager)
    : AGE::ECS::System(registry),
      resourceManager(manager) {}

void PlayerControlSystem::fireProjectile(ProjectileType type, const AGE::vec3<int> &pos) {
    auto bullet = AGE::ECS::Entity(registry->createEntity(), registry);
    auto *bulletProp = type == REGULAR ? resourceManager->at("bullet2").get()
                                       : resourceManager->at("bullet1").get();
    auto bulletPosition = AGE::vec3<int>(pos) + AGE::vec3<int>(1, 0, 0);
    bullet.addComponent(AGE::Components::TransformComponent(bulletPosition));
    bullet.addComponent(AGE::Components::AsciiRenderComponent(bulletProp));
    bullet.addComponent(AGE::Components::Velocity(AGE::vec3<int>(1, 0, 0)));
    bullet.addComponent(AGE::Components::EntityTagComponent("bullet"));
    if (type == REGULAR) {
        bullet.addComponent(AGE::Components::BoundingBoxComponent(AGE::vec2<int>(1, 1)));
    } else {
        bullet.addComponent(AGE::Components::BoundingBoxComponent(AGE::vec2<int>(3, 3), AGE::vec2<int>(-1, -1)));
    }
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
                case 'j':fireProjectile(REGULAR, transform.getPosition());
                    break;
                case 'k':fireProjectile(SPECIAL, transform.getPosition());
                    break;
                case 'w':transform.getPosition().y -= 1;
                    break;
                case 's':transform.getPosition().y += 1;
                    break;
                default:break;
            }
            auto &pos = transform.getPosition();
            if (pos.x <= 0) pos.x = 0;
            if (pos.y <= 0) pos.y = 0;
            if (pos.x > 79) pos.x = 79;
            if (pos.y > 24) pos.y = 24;
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
