//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_CHARACTERPROP_H_
#define FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_CHARACTERPROP_H_

#include "../IAsciiRenderProp.h"
#include "../../ScreenBuffer.h"

namespace AGE::Renderer {

class CharacterProp : public IAsciiRenderProp {
    char character;
  public:
    explicit CharacterProp(char c) : character{c} {}
    void render(AsciiRenderer *renderer, int xOffset, int yOffset) const override {
        renderer->drawCharacter(xOffset, yOffset, character);
    }
};

}

#endif //FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_CHARACTERPROP_H_
