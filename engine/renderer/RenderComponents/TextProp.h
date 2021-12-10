//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_TEXTPROP_H_
#define FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_TEXTPROP_H_

#include "AsciiRenderProp.h"

namespace AGE::Renderer {

class TextProp : public AsciiRenderProp {
    std::string text;
  public:
    explicit TextProp(std::string str) : text(std::move(str)) {}
    void render(AsciiRenderer *renderer, int xOffset, int yOffset) override {
        renderer->drawText(xOffset, yOffset, text);
    }
};

}

#endif //FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_TEXTPROP_H_
