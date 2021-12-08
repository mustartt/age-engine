//
// Created by henry on 2021-12-07.
//

#include "Scene.h"

namespace AGE {

void Scene::destroyEntity(const ECS::Entity &entity) {
    registry->destroyEntity(entity.getEntityId());
}

ECS::Entity Scene::createEntity() {
    // todo: add default components
    auto id = registry->createEntity();
    return ECS::Entity(id, registry.get());
}

}