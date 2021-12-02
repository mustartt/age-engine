#include <iostream>
#include "ncurses.h"

#include "engine/ecs/Registry.h"

int main() {
    using namespace AGE::ECS;

    struct Tag {
      std::string tag;
    };

    struct TagSystem : public System {
      public:
        explicit TagSystem(Registry *reg) : System(reg) {}
        void printTags() {
            for (auto const &entity: entities) {
                auto &entityTag = registry->getComponent<Tag>(entity);
                std::cout << "Object: " << entityTag.tag << std::endl;
            }
        }
        void testModification() {
            for (auto const &entity: entities) {
                auto &entityTag = registry->getComponent<Tag>(entity);
                entityTag.tag += '!';
            }
        }
    };

    Registry registry;

    registry.registerComponent<Tag>();

    auto tagSystem = registry.registerSystem<TagSystem>(&registry);
    Archetype archetype;
    archetype.push_back(registry.getComponentType<Tag>());
    registry.setSystemArchetype<TagSystem>(archetype);

    auto test = registry.createEntity();
    registry.addComponent<Tag>(test, {"TestEntityTag"});

    tagSystem->printTags();
    tagSystem->printTags();

}
