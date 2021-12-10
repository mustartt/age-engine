//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_CHARACTERPROP_H_
#define FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_CHARACTERPROP_H_

#include "AsciiRenderProp.h"
#include "renderer/ScreenBuffer.h"
#include "renderer/AsciiRenderer.h"

namespace AGE::Renderer {

class CharacterProp : public AsciiRenderProp {
    char character;
  public:
    explicit CharacterProp(char c) : character{c} {}
    void render(AsciiRenderer *renderer, int xOffset, int yOffset) override {
        renderer->drawCharacter(xOffset, yOffset, character);
    }
};

}

#endif //FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_CHARACTERPROP_H_
