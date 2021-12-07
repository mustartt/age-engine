#include <iostream>
#include <chrono>
#include <thread>

#include "ncurses.h"

#include "engine/ecs/impl/BasicRegistry.h"
#include "CursesContextManager.h"
#include "engine/ncurses/CursesKeyboard.h"

int main(int argc, char *argv[]) {
    CursesContextManager manager(std::make_unique<CursesRenderer>(0, 0));
    AGE::CursesKeyboard keyboard;

    int col = 0;
    for (int i = 0; i < 20; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        keyboard.captureInputs();

        std::optional<AGE::Keycode> key = keyboard.getKeycode();
        while (key) {
            mvaddch(1, col++, key.value());
            refresh();
            key = keyboard.getKeycode();
        }
        refresh();
    }

    return 0;
}
