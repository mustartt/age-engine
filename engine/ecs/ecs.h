//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_ECS_H_
#define FINAL_PROJECT_ENGINE_ECS_ECS_H_

#include <cstdint>
#include <vector>
#include <typeindex>

namespace AGE::ECS {

using EntityID = std::uint64_t;
using ComponentID = EntityID;
using Archetype = std::vector<ComponentID>;
using ComponentType = std::type_index;
using SystemType = std::type_index;

}

#endif //FINAL_PROJECT_ENGINE_ECS_ECS_H_
