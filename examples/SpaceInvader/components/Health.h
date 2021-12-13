//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_HEALTH_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_HEALTH_H_

#include <ecs/Entity.h>
#include <events/Event.h>
#include <events/EngineEvents/EngineEvents.h>
#include <renderer/RenderComponents/TextProp.h>

namespace SpaceInvader {

using namespace AGE;

class Health {
    int health;
    int total;
  public:
    explicit Health(int health, int total) : health(health), total(total) {};
    [[nodiscard]] int getHealth() const { return health; }
    [[nodiscard]] int getTotal() const { return total; }
    void setHealth(int newHealth) { this->health = std::clamp(newHealth, 0, total); }
    [[nodiscard]] bool dead() const { return health == 0; }
};

class PlayerHealthSystem : public ECS::System {
  public:
    explicit PlayerHealthSystem(ECS::Registry *registry) : System(registry) {}
    ~PlayerHealthSystem() override = default;
    void handleOutOfBound(EventQueue *queue) {
        for (auto entityId: entities) {
            auto entity = ECS::Entity(entityId, registry);
            auto &health = entity.getComponent<Health>();
            health.setHealth(health.getHealth() - 1);
            if (entity.hasComponent<Components::AsciiRenderComponent>()) {
                auto prop = entity.getComponent<Components::AsciiRenderComponent>().getRenderProp();
                auto textProp = dynamic_cast<Renderer::TextProp *>(prop);
                auto newHealthDisplay = std::to_string(health.getHealth());
                newHealthDisplay += '/';
                newHealthDisplay += std::to_string(health.getTotal());
                textProp->setText(newHealthDisplay);
            }
            if (health.dead()) {
                queue->enqueue<Events::SwitchSceneEvent>("game_over_scene");
            }
        }
    }
    ECS::Archetype getSystemArchetype() override {
        ECS::Archetype archetype;
        archetype.push_back(registry->getComponentType<Health>());
        return archetype;
    }
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_HEALTH_H_
