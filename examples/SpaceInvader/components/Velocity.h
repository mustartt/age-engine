//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_VELOCITY_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_VELOCITY_H_

#include <utils/vec3.h>

namespace SpaceInvader::CustomCS {

class Velocity {
    AGE::vec3<int> velocity;
  public:
    explicit Velocity(const AGE::vec3<int> &velocity) : velocity(velocity) {}
    [[nodiscard]] const AGE::vec3<int> &getVelocity() const { return velocity; }
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_VELOCITY_H_
