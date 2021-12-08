//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_COMPONENTS_ENGINECOMPONENTS_H_
#define FINAL_PROJECT_ENGINE_COMPONENTS_ENGINECOMPONENTS_H_

#include "../renderer/RenderComponents/AsciiRenderProp.h"
#include "../data/vec3.h"

#include <string>

namespace AGE::Components {

class EntityTagComponent {
    std::string tag;
  public:
    explicit EntityTagComponent(std::string tagName = "unknown_tag")
        : tag(std::move(tagName)) {}
    [[nodiscard]]
    const std::string &getTag() const { return tag; }
};

class TransformComponent {
    vec3<int> position;
  public:
    explicit TransformComponent(const vec3<int> &pos) : position(pos) {}
    vec3<int> &getPosition() { return position; }
};

class AsciiRenderComponent {
    Renderer::AsciiRenderProp *renderProp;
  public:
    explicit AsciiRenderComponent(Renderer::AsciiRenderProp *prop) : renderProp(prop) {}
    Renderer::AsciiRenderProp *getRenderProp() { return renderProp; }
};

}

#endif //FINAL_PROJECT_ENGINE_COMPONENTS_ENGINECOMPONENTS_H_
