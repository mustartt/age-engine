#include <iostream>
#include <chrono>
#include <thread>

#include "ncurses.h"

#include "engine/ncurses/CursesContextManager.h"
#include "engine/renderer/Renderer.h"
#include "engine/ncurses/CursesRenderAdapter.h"

[[noreturn]] void DEBUG_PAUSE() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(int argc, char *argv[]) {
    using namespace AGE;

    CursesContextManager manager(80, 25);
    auto renderer = manager.getRendererInstance();
    Renderer::RenderTarget *adapter = new Renderer::CursesRenderAdapter(renderer);
    ConcreteRenderer concreteRenderer(adapter, 80, 25);

    for (int x = 0; x < 80; ++x) {
        for (int y = 0; y < 25; ++y) {
            concreteRenderer.clear();
            concreteRenderer.drawCharacter(x, y, '@');
            concreteRenderer.draw();
            // std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
    renderer->update();

    DEBUG_PAUSE();
    return 0;
}
