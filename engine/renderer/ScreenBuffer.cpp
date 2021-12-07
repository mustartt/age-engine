//
// Created by henry on 2021-12-01.
//

#include <cassert>

#include "ScreenBuffer.h"

namespace AGE::Renderer {

ScreenBuffer::ScreenBuffer(size_t width, size_t height)
    : width{width}, height{height},
      buffer{} {
    for (int i = 0; i < height; ++i) {
        buffer.emplace_back(width, ' ');
    }
}

void ScreenBuffer::drawCharacter(int x, int y, char c) {
    assert(0 <= x && x < width && "invalid x screen buffer pos");
    assert(0 <= x && x < width && "invalid y screen buffer pos");
    buffer[y][x] = c;
}

}

