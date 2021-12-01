//
// Created by henry on 2021-12-01.
//

#include <cassert>

#include "ScreenBuffer.h"

namespace AGE {
namespace Renderer {

ScreenBuffer::ScreenBuffer(int width, int height)
    : width{width}, height{height},
      buffer{std::make_unique<char>(width * height)} {
    std::fill(buffer.get(), buffer.get() + width * height, ' ');
}

void ScreenBuffer::drawCharacter(int x, int y, char c) {
    assert(0 <= x && x < width && "invalid x screen buffer pos");
    assert(0 <= x && x < width && "invalid y screen buffer pos");
    buffer.get()[y * width + x] = c;
}

}
}

