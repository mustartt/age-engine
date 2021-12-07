//
// Created by henry on 2021-12-07.
//

#include "ncurses.h"
#include "CursesKeyboard.h"

namespace AGE {

CursesKeyboard::CursesKeyboard() {
    if (nodelay(stdscr, TRUE) == ERR) {
        // throw NoDelayUnavailableException{};
    }
}

CursesKeyboard::~CursesKeyboard() = default;

void CursesKeyboard::captureInputs() {
    int key;
    while ((key = getch()) != ERR) {
        keycodeBuffer.push_back(key);
    }
}

std::optional<Keycode> CursesKeyboard::getKeycode() {
    if (keycodeBuffer.empty()) return {};
    Keycode key = keycodeBuffer.front();
    keycodeBuffer.pop_front();
    return std::make_optional<Keycode>(key);
}

void CursesKeyboard::flush() {
    keycodeBuffer.erase(keycodeBuffer.begin(), keycodeBuffer.end());
}

}
