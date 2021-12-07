//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_SCREENBUFFER_H_
#define FINAL_PROJECT_ENGINE_RENDERER_SCREENBUFFER_H_

#include <memory>
#include <vector>
#include <string>

namespace AGE::Renderer {

class ScreenBuffer {
    size_t width;
    size_t height;
    std::vector<std::string> buffer;
  public:
    explicit ScreenBuffer(size_t width, size_t height);
    ~ScreenBuffer() = default;

    [[nodiscard]] size_t getWidth() const { return width; }
    [[nodiscard]] size_t getHeight() const { return height; }
    std::vector<std::string> &getBuffer() { return buffer; }
    std::string &getLine(int line) { return buffer[line]; }

    void drawCharacter(int x, int y, char c);
};

}

#endif //FINAL_PROJECT_ENGINE_RENDERER_SCREENBUFFER_H_
