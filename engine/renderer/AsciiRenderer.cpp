//
// Created by henry on 2021-12-01.
//

#include "AsciiRenderer.h"

namespace AGE {

AsciiRenderer::AsciiRenderer(Renderer::RenderTarget *target, int width, int height)
    : width{width}, height{height},
      screenBuffer(width, height),
      renderTarget{target} {}

void AsciiRenderer::drawCharacter(int x, int y, char c) {
    if (x < 0 || x >= screenBuffer.getWidth()) return;
    if (y < 0 || y >= screenBuffer.getHeight()) return;
    screenBuffer.drawCharacter(x, y, c);
}

void AsciiRenderer::drawText(int x, int y, const std::string &text) {
    for (int i = 0; i < text.length(); ++i) {
        drawCharacter(x + i, y, text[i]);
    }
}

void AsciiRenderer::drawRect(int x, int y, int w, int h, char fill) {
    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            drawCharacter(x + c, y + r, fill);
        }
    }
}

void AsciiRenderer::drawRect(int x, int y, int w, int h, char border, char fill) {
    drawRect(x, y, w, h, fill);
    drawRect(x, y, w, 1, border);              // top
    drawRect(x, y + h, w, 1, border);       // bottom
    drawRect(x, y, 1, h, border);             // left
    drawRect(x + h, y, w, 1, border);       // right
}

void AsciiRenderer::clear() {
    drawRect(0, 0, width, height, ' ');
}

void AsciiRenderer::draw() {
    renderTarget->render(screenBuffer);
}

}
