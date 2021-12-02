#include <iostream>
#include "ncurses.h"

#include "engine/ecs/Registry.h"

int main() {
    using namespace AGE::ECS;

    struct Tag {
      std::string tag;
    };
    struct UpdateChar {
      char c;
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
                auto &updateChar = registry->getComponent<UpdateChar>(entity);
                entityTag.tag += updateChar.c;
            }
        }
    };

    Registry registry;

    registry.registerComponent<Tag>();
    registry.registerComponent<UpdateChar>();

    auto tagSystem = registry.registerSystem<TagSystem>(&registry);
    Archetype archetype;
    archetype.push_back(registry.getComponentType<Tag>());
    archetype.push_back(registry.getComponentType<UpdateChar>());
    registry.setSystemArchetype<TagSystem>(archetype);

    auto test = registry.createEntity();
    registry.addComponent<Tag>(test, {"TestEntityTag"});
    registry.addComponent<UpdateChar>(test, {'?'});

    tagSystem->printTags();
    for (int i = 0; i < 10; ++i) {
        tagSystem->testModification();
    }
    tagSystem->printTags();

}
