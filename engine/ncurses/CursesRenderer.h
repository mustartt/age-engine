//
// Created by henry on 2021-11-20.
//

#ifndef FINAL_PROJECT__CURSESRENDERER_H_
#define FINAL_PROJECT__CURSESRENDERER_H_

#include <exception>
#include <ncurses.h>
#include "../renderer/ScreenBuffer.h"

namespace AGE {

class InvalidBufferSizeException : std::exception {};

class CursesRenderer {
    int width;
    int height;
    WINDOW *window;
  public:
    explicit CursesRenderer(int width, int height);
    ~CursesRenderer();

    void drawBuffer(Renderer::ScreenBuffer &buffer) const;
    void update() const;
};

}

#endif //FINAL_PROJECT__CURSESRENDERER_H_
