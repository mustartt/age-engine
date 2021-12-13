//
// Created by henry on 2021-12-12.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_PLAYERSCORE_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_PLAYERSCORE_H_

#include <ecs/Entity.h>

namespace SpaceInvader {

using namespace AGE;

struct PlayerScore {
  int score;
};

class PlayerScoreSystem : public ECS::System {
  public:
    explicit PlayerScoreSystem(ECS::Registry *registry);
    ~PlayerScoreSystem() override = default;
    void playerScoreHandler();
    ECS::Archetype getSystemArchetype() override;
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_PLAYERSCORE_H_
