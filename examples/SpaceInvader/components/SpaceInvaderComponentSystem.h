//
// Created by henry on 2021-12-08.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_SPACEINVADERCOMPONENTSYSTEM_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_SPACEINVADERCOMPONENTSYSTEM_H_

#include <algorithm>
#include <ecs/SystemManager.h>
#include <ecs/Entity.h>

#include <components/EngineComponents.h>

namespace SpaceInvader::CustomCS {

class Health {
    int health;
    int total;
  public:
    explicit Health(int health, int total) : health(health), total(total) {};
    [[nodiscard]] int getHealth() const { return health; }
    [[nodiscard]] int getTotal() const { return total; }
    void setHealth(int newHealth) { this->health = std::clamp(newHealth, 0, total); }
};

class Velocity {
    AGE::vec3<int> velocity;
  public:
    explicit Velocity(const AGE::vec3<int> &velocity) : velocity(velocity) {}
    [[nodiscard]] const AGE::vec3<int> &getVelocity() const { return velocity; }
};

class RemoveOnOutOfBoundComponent {
    vec3<int> top;
    vec3<int> bottom;
    int buffer;
  public:
    explicit RemoveOnOutOfBoundComponent(const vec3<int> &top,
                                         const vec3<int> &bottom,
                                         int buffer = 0)
        : top(top), bottom(bottom), buffer(buffer) {}
    bool isOutOfBound(const vec3<int> &position) {
        return outOfBound(top.x, bottom.x, position.x)
            || outOfBound(top.y, bottom.y, position.y)
            || outOfBound(top.z, bottom.z, position.z);
    }
  private:
    [[nodiscard]] bool outOfBound(int x1, int x2, int val) const {
        return val < x1 - buffer || val >= x2 + buffer;
    }
};

class PhysicsSystem : public AGE::ECS::System {
    /* uses TransformComponent, Velocity */
  public:
    explicit PhysicsSystem(AGE::ECS::Registry *registry) : AGE::ECS::System(registry) {}
    ~PhysicsSystem() = default;
    void update() {
        for (auto entityId: entities) {
            auto entity = AGE::ECS::Entity(entityId, registry);
            auto &position = entity.getComponent<AGE::Components::TransformComponent>();
            auto &velocity = entity.getComponent<CustomCS::Velocity>();
            position.getPosition() += velocity.getVelocity();
        }
    }
    AGE::ECS::Archetype getSystemArchetype() override {
        using namespace AGE;
        ECS::Archetype archetype;
        archetype.push_back(registry->getComponentType<Components::TransformComponent>());
        archetype.push_back(registry->getComponentType<CustomCS::Velocity>());
        return archetype;
    }
};

enum ProjectileType { REGULAR, SPECIAL, ENEMY };
using ResourceManager = std::unordered_map<std::string, std::unique_ptr<Renderer::AsciiRenderProp>>;

class PlayerControlSystem : public AGE::ECS::System {
    /* uses TransformComponent, EntityTagComponent */
    ResourceManager *resourceManager;
  public:
    explicit PlayerControlSystem(AGE::ECS::Registry *registry, ResourceManager *manager)
        : AGE::ECS::System(registry),
          resourceManager(manager) {}
    void fireProjectile(ProjectileType type, const AGE::vec3<int> &pos) {
        auto bullet = AGE::ECS::Entity(registry->createEntity(), registry);
        auto *bulletProp = resourceManager->at("bullet2").get();
        auto bulletPosition = vec3<int>(pos) + vec3<int>(0, -1, 0);
        bullet.addComponent(AGE::Components::TransformComponent(bulletPosition));
        bullet.addComponent(AGE::Components::AsciiRenderComponent(bulletProp));
        bullet.addComponent(CustomCS::Velocity(vec3<int>(0, -1, 0)));
        bullet.addComponent(AGE::Components::EntityTagComponent("bullet"));
        bullet.addComponent(AGE::Components::BoundingBoxComponent(vec2<int>(1, 1)));
        bullet.addComponent(CustomCS::RemoveOnOutOfBoundComponent(
            vec3<int>(0, 5, -100),
            vec3<int>(80, 25, 100)));
    }
    void move(int keycode) {
        for (auto &entityId: entities) {
            auto entity = ECS::Entity(entityId, registry);
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
    ECS::Archetype getSystemArchetype() override {
        using namespace AGE;
        ECS::Archetype archetype;
        archetype.push_back(registry->getComponentType<Components::TransformComponent>());
        archetype.push_back(registry->getComponentType<Components::EntityTagComponent>());
        return archetype;
    }
};

class MeteorBulletCollisionSystem : public ECS::System {
  public:
    explicit MeteorBulletCollisionSystem(AGE::ECS::Registry *registry) : AGE::ECS::System(registry) {}
    void handleCollisions(Events::BasicCollisionEvent *event, EventQueue *eventQueue) {
        try { // handle collisions gets called in the next tick so entities might be deleted already
            auto entity1 = event->getCollidingPair().first;
            auto entity2 = event->getCollidingPair().second;
            std::map<std::string, ECS::Entity> res{
                {entity1.getComponent<Components::EntityTagComponent>().getTag(), entity1},
                {entity2.getComponent<Components::EntityTagComponent>().getTag(), entity2}
            };
            if (res.count("bullet") && res.count("meteor")) {
                entity1.destroyEntity();
                entity2.destroyEntity();
            }
        } catch (...) {}
    }
    ECS::Archetype getSystemArchetype() override {
        AGE::ECS::Archetype archetype;
        archetype.push_back(registry->getComponentType<Components::TransformComponent>());
        archetype.push_back(registry->getComponentType<Components::BoundingBoxComponent>());
        return archetype;
    }
};

class OutOfBoundSystem : public ECS::System {
  public:
    explicit OutOfBoundSystem(AGE::ECS::Registry *registry)
        : AGE::ECS::System(registry) {}
    void removeOutOfBoundEntities() {
        for (auto entityId: entities) {
            ECS::Entity entity(entityId, registry);
            auto &bound = entity.getComponent<RemoveOnOutOfBoundComponent>();
            auto &pos = entity.getComponent<Components::TransformComponent>();
            if (bound.isOutOfBound(pos.getPosition())) {
                entity.destroyEntity();
            }
        }
    }
    ECS::Archetype getSystemArchetype() override {
        AGE::ECS::Archetype archetype;
        archetype.push_back(registry->getComponentType<CustomCS::RemoveOnOutOfBoundComponent>());
        archetype.push_back(registry->getComponentType<Components::TransformComponent>());
        return archetype;
    }
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_SPACEINVADERCOMPONENTSYSTEM_H_
