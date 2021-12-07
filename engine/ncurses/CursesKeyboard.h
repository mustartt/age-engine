//
// Created by henry on 2021-12-07.
//

#ifndef FINAL_PROJECT_ENGINE_NCURSES_CURSESKEYBOARD_H_
#define FINAL_PROJECT_ENGINE_NCURSES_CURSESKEYBOARD_H_

#include <list>
#include <optional>

namespace AGE {

using Keycode = int;

class NoDelayUnavailableException : std::exception {};

class CursesKeyboard {
    std::list<Keycode> keycodeBuffer;
  public:
    CursesKeyboard();
    ~CursesKeyboard();

    void captureInputs();
    std::optional<Keycode> getKeycode();
    void flush();
};

}

#endif //FINAL_PROJECT_ENGINE_NCURSES_CURSESKEYBOARD_H_
