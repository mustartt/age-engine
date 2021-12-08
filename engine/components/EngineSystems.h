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
    }
};

}

#endif //FINAL_PROJECT_ENGINE_COMPONENTS_ENGINESYSTEMS_H_
