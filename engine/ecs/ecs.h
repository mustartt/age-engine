//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_ECS_ECS_H_
#define FINAL_PROJECT_ENGINE_ECS_ECS_H_

namespace AGE {
namespace ECS {

using EntityID = std::uint64_t;
using ComponentID = EntityID;
using Archtype = std::vector<ComponentID>;
using ComponentType = std::type_info;

class Registry {

};

}
}

#endif //FINAL_PROJECT_ENGINE_ECS_ECS_H_
