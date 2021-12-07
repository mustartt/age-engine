//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_RENDERER_H_
#define FINAL_PROJECT_ENGINE_RENDERER_RENDERER_H_

#include <cstdio>
#include <string>

#include "ScreenBuffer.h"
#include "RenderTarget.h"

namespace AGE {

class ConcreteRenderer {
    int width;
    int height;
    Renderer::ScreenBuffer screenBuffer;
    Renderer::RenderTarget *renderTarget;
  public:
    ConcreteRenderer(Renderer::RenderTarget *target, int width, int height);
    ~ConcreteRenderer() = default;

    void drawCharacter(int x, int y, char c);
    void drawText(int x, int y, const std::string &text);
    void drawRect(int x, int y, int w, int h, char fill);
    void drawRect(int x, int y, int w, int h, char border, char fill);
    void clear();

    void draw();
};
}

#endif //FINAL_PROJECT_ENGINE_RENDERER_RENDERER_H_
