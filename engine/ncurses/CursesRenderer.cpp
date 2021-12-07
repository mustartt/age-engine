//
// Created by henry on 2021-11-20.
//

#include "CursesRenderer.h"

namespace AGE {

CursesRenderer::CursesRenderer(int width, int height) : width{width}, height{height} {
    window = newwin(height, width, 0, 0);
    wrefresh(window);
}

CursesRenderer::~CursesRenderer() {
    delwin(window);
};

void CursesRenderer::drawBuffer(Renderer::ScreenBuffer &buffer) const {
    if (buffer.getWidth() != width || buffer.getHeight() != height) {
        throw InvalidBufferSizeException{};
    }
    for (int r = 0; r < buffer.getHeight(); ++r) {
        mvwprintw(window, r, 0, buffer.getLine(r).c_str());
    }
}

[[maybe_unused]] void CursesRenderer::update() const {
    wrefresh(window);
}

}
