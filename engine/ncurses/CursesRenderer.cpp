//
// Created by henry on 2021-11-20.
//

#include "CursesRenderer.h"
#include <ncurses.h>

namespace AGE {

CursesRenderer::CursesRenderer(int width, int height) : width{width}, height{height} {
    update(); // calls to refresh before any draw calls occurs
}

CursesRenderer::~CursesRenderer() = default;

void CursesRenderer::drawBuffer(Renderer::ScreenBuffer &buffer) const {
    if (buffer.getWidth() != width || buffer.getHeight() != height) {
        throw InvalidBufferSizeException{};
    }
    auto buf = buffer.getRawBufferContent();
    for (int x = 0; x < buffer.getWidth(); ++x) {
        for (int y = 0; y < buffer.getHeight(); ++y) {
            mvaddch(y, x, buf[y * width + x]);
        }
    };
}

[[maybe_unused]] void CursesRenderer::update() const {
    refresh();
}

}
