//
// Created by henry on 2021-12-09.
//

#include "AsciiRender.h"
#include "Transform.h"

#include <ecs/Entity.h>
#include <map>
#include <utils/vec3.h>
#include <renderer/AsciiRenderer.h>
#include <renderer/RenderComponents/AsciiRenderProp.h>

namespace AGE::Systems {
void AGE::Systems::AsciiRenderSystem::render() {
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

    // debug: entity counts
    auto count = std::to_string(entities.size());
    renderer->drawText(0, 24, count);

    renderer->draw();
}

ECS::Archetype AsciiRenderSystem::getSystemArchetype() {
    ECS::Archetype archetype;
    archetype.push_back(registry->getComponentType<Components::TransformComponent>());
    archetype.push_back(registry->getComponentType<Components::AsciiRenderComponent>());
    return archetype;
}

}


