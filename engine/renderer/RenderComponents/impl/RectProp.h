//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_RECTPROP_H_
#define FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_RECTPROP_H_

#include "../AsciiRenderProp.h"
#include "../../ScreenBuffer.h"

namespace AGE::Renderer {

class RectProp : public AsciiRenderProp {
    char character;
    int width;
    int height;
  public:
    explicit RectProp(char c, int w, int h) : character{c}, width{w}, height{h} {}
    void render(AsciiRenderer *renderer, int xOffset, int yOffset) override {
        renderer->drawRect(xOffset, yOffset, width, height, c);
    }
};

}

#endif //FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_RECTPROP_H_
