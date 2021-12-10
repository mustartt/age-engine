//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_ECS_H_
#define FINAL_PROJECT_ENGINE_ECS_ECS_H_

#include <cstdint>
#include <vector>

namespace AGE::ECS {

using EntityID = std::uint64_t;
using ComponentID = EntityID;
using Archetype = std::vector<ComponentID>;
using ComponentType = const char *;
using SystemType = const char *;

}

#endif //FINAL_PROJECT_ENGINE_ECS_ECS_H_
