//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_ENGINE_COMPONENTS_TRANSFORM_H_
#define FINAL_PROJECT_ENGINE_COMPONENTS_TRANSFORM_H_

#include "utils/vec3.h"

namespace AGE::Components {

class TransformComponent {
    vec3<int> position;
  public:
    explicit TransformComponent(const vec3<int> &pos) : position(pos) {}
    vec3<int> &getPosition() { return position; }
};

}

#endif //FINAL_PROJECT_ENGINE_COMPONENTS_TRANSFORM_H_
