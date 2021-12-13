//
// Created by henry on 2021-12-09.
//

#include <ecs/Entity.h>
#include <components/Transform.h>
#include <components/AsciiRender.h>
#include <components/EntityTag.h>
#include <components/BasicCollision.h>
#include <utils/vec2.h>
#include <components/None.h>
#include <components/Physics.h>
#include "MeteorSpawn.h"
#include "OutOfBound.h"

namespace SpaceInvader::CustomCS {

MeteorSpawnSystem::MeteorSpawnSystem(AGE::ECS::Registry *registry, ResourceManager *manager)
    : System(registry), resources(manager) {
    rng.seed(1234);
}

void MeteorSpawnSystem::spawnMeteor(int pos) {
    using namespace AGE;
    auto meteor = ECS::Entity(registry->createEntity(), registry);

    meteor.addComponent(Components::TransformComponent(vec3<int>(75, pos, 0)));
    meteor.addComponent(Components::AsciiRenderComponent(resources->at("meteor2").get()));
    meteor.addComponent(Components::EntityTagComponent("meteor"));
    meteor.addComponent(Components::Velocity(vec3<int>(-1, 0, 0)));
    meteor.addComponent(Components::BoundingBoxComponent(vec2<int>(1, 1)));
    meteor.addComponent(CustomCS::RemoveOnOutOfBoundComponent(
        vec3<int>(0, 0, -1), vec3<int>(80, 20, 1), 0));
}

void MeteorSpawnSystem::spawn() {
    if (lifetime % spawnInterval == 0) {
        int spawnCount = 1;
        std::uniform_int_distribution<int> randomPosition(2, 18);
        std::set<int> spawnPos;
        for (int i = 0; i < spawnCount; ++i) spawnPos.insert(randomPosition(rng));
        for (auto pos: spawnPos) spawnMeteor(pos);
    }
    ++lifetime;
}

AGE::ECS::Archetype MeteorSpawnSystem::getSystemArchetype() {
    using namespace AGE;
    ECS::Archetype archetype;
    archetype.push_back(registry->getComponentType<Components::None>());
    return archetype;
}

}
