//
// Created by henry on 2021-12-12.
//

#include "PlayerScore.h"

#include <components/AsciiRender.h>
#include <renderer/RenderComponents/TextProp.h>

namespace SpaceInvader {

using namespace AGE;

PlayerScoreSystem::PlayerScoreSystem(AGE::ECS::Registry *registry) : System(registry) {}

void PlayerScoreSystem::playerScoreHandler() {
    for (auto entityId: entities) {
        auto entity = ECS::Entity(entityId, registry);
        if (!entity.isValid()) continue;
        auto &score = entity.getComponent<PlayerScore>();
        score.score += 10; // score
        if (entity.hasComponent<Components::AsciiRenderComponent>()) {
            auto &render = entity.getComponent<Components::AsciiRenderComponent>();
            auto prop = dynamic_cast<Renderer::TextProp *>(render.getRenderProp());
            if (!prop) return;
            prop->setText(std::to_string(score.score));
        }
    }
}

ECS::Archetype PlayerScoreSystem::getSystemArchetype() {
    ECS::Archetype archetype;
    archetype.push_back(registry->getComponentType<PlayerScore>());
    return archetype;
}

}
