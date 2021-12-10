//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_METEORSPAWN_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_METEORSPAWN_H_

#include <random>
#include <ecs/SystemManager.h>
#include "Player.h"

namespace SpaceInvader::CustomCS {

class MeteorSpawnSystem : public AGE::ECS::System {
    using RngGen = std::mt19937;
    RngGen rng;
    int lifetime = 0;
    int spawnInterval = 20;
    ResourceManager* resources;
  public:
    explicit MeteorSpawnSystem(AGE::ECS::Registry *registry, ResourceManager* manager);
    ~MeteorSpawnSystem() override = default;
    void spawn();
    AGE::ECS::Archetype getSystemArchetype() override;
  private:
    void spawnMeteor(int pos);
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_METEORSPAWN_H_
