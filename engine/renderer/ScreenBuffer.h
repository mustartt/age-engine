//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_SCREENBUFFER_H_
#define FINAL_PROJECT_ENGINE_RENDERER_SCREENBUFFER_H_

#include <memory>

namespace AGE::Renderer {

class ScreenBuffer {
    int width;
    int height;
    std::unique_ptr<char> buffer;
  public:
    explicit ScreenBuffer(int width, int height);
    ~ScreenBuffer() = default;

    [[nodiscard]] int getWidth() const { return width; }
    [[nodiscard]] int getHeight() const { return height; }
    [[nodiscard]] char *getRawBufferContent() const { return buffer.get(); }

    void drawCharacter(int x, int y, char c);
};

}

#endif //FINAL_PROJECT_ENGINE_RENDERER_SCREENBUFFER_H_
