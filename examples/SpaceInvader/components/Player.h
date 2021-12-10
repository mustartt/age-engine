//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_PLAYER_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_PLAYER_H_

#include <unordered_map>
#include <string>
#include <memory>
#include <ecs/Entity.h>
#include <renderer/RenderComponents/AsciiRenderProp.h>
#include <utils/vec3.h>

namespace SpaceInvader::CustomCS {

enum ProjectileType { REGULAR, SPECIAL, ENEMY };
using ResourceManager = std::unordered_map<std::string, std::unique_ptr<AGE::Renderer::AsciiRenderProp>>;

class PlayerControlSystem : public AGE::ECS::System {
    /* uses TransformComponent, EntityTagComponent */
    ResourceManager *resourceManager;
  public:
    explicit PlayerControlSystem(AGE::ECS::Registry *registry, ResourceManager *manager);
    void fireProjectile(ProjectileType type, const AGE::vec3<int> &pos);
    void move(int keycode);
    AGE::ECS::Archetype getSystemArchetype() override;
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_PLAYER_H_
