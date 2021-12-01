//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_SCREENBUFFER_H_
#define FINAL_PROJECT_ENGINE_RENDERER_SCREENBUFFER_H_

#include <memory>

namespace AGE {
namespace Renderer {

class ScreenBuffer {
    int width;
    int height;
    std::unique_ptr<char> buffer;
  public:
    explicit ScreenBuffer(int width, int height);
    ~ScreenBuffer() = default;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    char *getRawBufferContent() const { return buffer.get(); }

    void drawCharacter(int x, int y, char c);
};

}
}

#endif //FINAL_PROJECT_ENGINE_RENDERER_SCREENBUFFER_H_
