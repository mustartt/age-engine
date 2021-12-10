//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_ENGINE_COMPONENTS_ASCIIRENDER_H_
#define FINAL_PROJECT_ENGINE_COMPONENTS_ASCIIRENDER_H_

#include <ecs/SystemManager.h>

namespace AGE {
class AsciiRenderer;
namespace Renderer {
class AsciiRenderProp;
}
}

namespace AGE::Components {

class AsciiRenderComponent {
    Renderer::AsciiRenderProp *renderProp;
  public:
    explicit AsciiRenderComponent(Renderer::AsciiRenderProp *prop) : renderProp(prop) {}
    Renderer::AsciiRenderProp *getRenderProp() { return renderProp; }
};

}

namespace AGE::Systems {

// uses TransformComponent, AsciiRenderComponent
class AsciiRenderSystem : public ECS::System {
    AsciiRenderer *renderer;
  public:
    explicit AsciiRenderSystem(ECS::Registry *registry)
        : ECS::System(registry), renderer{nullptr} {}
    void setRenderer(AsciiRenderer *asciiRenderer) { renderer = asciiRenderer; }
    void render();
    ECS::Archetype getSystemArchetype() override;
};
}

#endif //FINAL_PROJECT_ENGINE_COMPONENTS_ASCIIRENDER_H_
