//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_RECTPROP_H_
#define FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_RECTPROP_H_

#include "../IAsciiRenderProp.h"
#include "../../ScreenBuffer.h"

namespace AGE {
namespace Renderer {

class RectProp : public IAsciiRenderProp {
    char character;
    int width;
    int height;
  public:
    explicit CharacterProp(char c, int w, int h) : character{c}, width{w}, height{h} {}
    void render(ScreenBuffer buffer, int xOffset, int yOffset) override {
        for (int x = 0; x <= w; ++x) {
            for (int y = 0; y <= h; ++y) {
                buffer.drawCharacter(xOffset + x, yOffset + y, character);
            }
        }
    }
};

}
}

#endif //FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_RECTPROP_H_
