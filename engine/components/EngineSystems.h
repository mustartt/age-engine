//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_COMPONENTS_ENGINESYSTEMS_H_
#define FINAL_PROJECT_ENGINE_COMPONENTS_ENGINESYSTEMS_H_

#include "../ecs/Entity.h"
#include "../renderer/AsciiRenderer.h"
#include "../renderer/RenderComponents/AsciiRenderProp.h"
#include "../components/EngineComponents.h"

#include <map>

namespace AGE::Systems {

// uses TransformComponent, AsciiRenderComponent
class AsciiRenderSystem : public ECS::System {
    AsciiRenderer *renderer{nullptr};
  public:
    explicit AsciiRenderSystem(ECS::Registry *registry)
        : ECS::System(registry) {}
    void setRenderer(AsciiRenderer *asciiRenderer) { renderer = asciiRenderer; }
    void render() {
        renderer->clear();
        std::map<int, std::vector<ECS::Entity>> renderLayer;
        for (auto &entityId: entities) {
            auto entity = ECS::Entity(entityId, registry);
            auto &transform = entity.getComponent<Components::TransformComponent>();
            vec3<int> &pos = transform.getPosition();
            renderLayer[pos.z].push_back(entity);
        }
        for (auto &pair: renderLayer) {
            for (auto &entity: pair.second) {
                auto &prop = entity.getComponent<Components::AsciiRenderComponent>();
                auto &transform = entity.getComponent<Components::TransformComponent>();
                prop.getRenderProp()->render(renderer, transform.getPosition().x, transform.getPosition().y);
            }
        }
        renderer->draw();
    }
};

// uses TransformComponent, EntityTagComponent
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
                    default:break;
                }
            }
        }
    }
};

}

#endif //FINAL_PROJECT_ENGINE_COMPONENTS_ENGINESYSTEMS_H_
