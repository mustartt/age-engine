//
// Created by henry on 2021-12-12.
//

#ifndef FINAL_PROJECT_ENGINE_COMPONENTS_BASICPLAYERMOVEMENT_H_
#define FINAL_PROJECT_ENGINE_COMPONENTS_BASICPLAYERMOVEMENT_H_

#include <ecs/Entity.h>

namespace AGE::Systems {

class PlayerWASDControlSystem : public ECS::System {
  public:
    explicit PlayerWASDControlSystem(ECS::Registry *registry) : ECS::System(registry) {}
    void move(int keycode) {
        for (auto &entityId: entities) {
            auto entity = ECS::Entity(entityId, registry);
            auto &tag = entity.getComponent<Components::EntityTagComponent>();
            if (tag.getTag() == "PlayerWASD") {
                auto &transform = entity.getComponent<Components::TransformComponent>();
                switch (keycode) {
                    case 'w':transform.getPosition().y -= 1;
                        break;
                    case 'a':transform.getPosition().x -= 1;
                        break;
                    case 's':transform.getPosition().y += 1;
                        break;
                    case 'd':transform.getPosition().x += 1;
                        break;
                    case 'q':transform.getPosition().z -= 1;
                        break;
                    case 'e':transform.getPosition().z += 1;
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
    ECS::Archetype getSystemArchetype() override {
        ECS::Archetype archetype;
        archetype.push_back(registry->getComponentType<Components::TransformComponent>());
        archetype.push_back(registry->getComponentType<Components::EntityTagComponent>());
        return archetype;
    }
};

}

#endif //FINAL_PROJECT_ENGINE_COMPONENTS_BASICPLAYERMOVEMENT_H_
