#include <memory>

#include "ncurses.h"
#include "CursesContextManager.h"

namespace AGE {

CursesContextManager::CursesContextManager(int width, int height)
    : renderer(std::make_unique<CursesRenderer>(width, height)),
      keyboard(std::make_unique<CursesKeyboard>()) {
    initscr();
    cbreak();
    noecho();
}

CursesContextManager::~CursesContextManager() {
    endwin();
}

}
