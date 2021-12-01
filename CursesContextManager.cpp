#include <memory>

#include "ncurses.h"
#include "CursesContextManager.h"
#include "CursesRenderer.h"

CursesContextManager::CursesContextManager(std::unique_ptr<CursesRenderer> renderer)
    : renderer_(std::move(renderer)) {
    initscr();
    cbreak();
    noecho();
}

CursesContextManager::~CursesContextManager() {
    endwin();
}
