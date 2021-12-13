//
// Created by henry on 2021-12-08.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_SPACEINVADERCOMPONENTSYSTEM_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_SPACEINVADERCOMPONENTSYSTEM_H_

#include <algorithm>
#include <ecs/SystemManager.h>
#include <ecs/Entity.h>
#include <map>
#include <components/Transform.h>
#include <components/AsciiRender.h>
#include <components/EntityTag.h>
#include <components/BasicCollision.h>

namespace SpaceInvader::CustomCS {

class MeteorBulletCollisionSystem : public ECS::System {
  public:
    explicit MeteorBulletCollisionSystem(AGE::ECS::Registry *registry) : AGE::ECS::System(registry) {}
    void handleCollisions(Events::BasicCollisionEvent *event, EventQueue *eventQueue) {
        try { // handle collisions gets called in the next tick so entities might be deleted already
            auto entity1 = event->getCollidingPair().first;
            auto entity2 = event->getCollidingPair().second;
            if (!entity1.isValid() || !entity2.isValid()) return;
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

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_SPACEINVADERCOMPONENTSYSTEM_H_
