//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_RENDERER_H_
#define FINAL_PROJECT_ENGINE_RENDERER_RENDERER_H_

#include <cstdio>
#include <string>

#include "ScreenBuffer.h"

namespace AGE {

class ConcreteRenderer {
    int width;
    int height;
    Renderer::ScreenBuffer screen_buffer;
  public:
    void drawCharacter(size_t x, size_t y, char c);
    void drawText(size_t x, size_t y, const std::string &text);
    void drawRect(size_t x, size_t y, size_t w, size_t h, char fill);
    void drawRect(size_t x, size_t y, size_t w, size_t h, char border, char fill);
    void clear();

    void draw();
};
}

#endif //FINAL_PROJECT_ENGINE_RENDERER_RENDERER_H_
