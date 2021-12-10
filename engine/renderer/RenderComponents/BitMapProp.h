//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_BITMAPPROP_H_
#define FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_BITMAPPROP_H_

#include <utility>
#include <vector>
#include <utility>

#include "utils/vec2.h"

#include "AsciiRenderProp.h"
#include "renderer/ScreenBuffer.h"

namespace AGE::Renderer {

using BitMap = std::vector<std::pair<vec2 < int>, char>>;

class BitMapProp : public AsciiRenderProp {
    BitMap bitmap{};
  public:
    explicit BitMapProp(BitMap bitmap) : bitmap{std::move(bitmap)} {}
    void render(AsciiRenderer *renderer, int xOffset, int yOffset) override {
        for (auto &pair: bitmap) {
            auto offset = vec2<int>(xOffset, yOffset);
            auto pos = pair.first + offset;
            renderer->drawCharacter(pos.x, pos.y, pair.second);
        }
    }
};

}

#endif //FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IMPL_BITMAPPROP_H_
