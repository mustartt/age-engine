//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_BITMAPPROP_H_
#define FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_BITMAPPROP_H_

#include <vector>
#include <pair>

#include "../../../data/vec2.h"

#include "../IAsciiRenderProp.h"
#include "../../ScreenBuffer.h"

namespace AGE {
namespace Renderer {

using BitMap = std::vector<std::pair<vec2i, char c>>;

class BitMapProp : public IAsciiRenderProp {
    BitMap bitmap{};
  public:
    explicit BitMapProp(BitMap bitmap) : bitmap{std::move{bitmap}} {}
    void render(ScreenBuffer buffer, int xOffset, int yOffset) override {
        for (auto &pair: bitmap) {
            auto pos = pair.first + vec2i(xOffset, yOffset);
            buffer.drawCharacter(pos.x, pos.y, pair.second);
        }
    }
};

}
}

#endif //FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_BITMAPPROP_H_
