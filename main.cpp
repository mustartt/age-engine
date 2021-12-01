#include <iostream>
#include "ncurses.h"

int main() {
    initscr();
    cbreak();

    WINDOW *window = newwin(25, 80, 0, 0);
    refresh();

    box(window, 0, 0);
    mvwprintw(window, 1, 1, "Hello World!");

    wrefresh(window);

    getch();

    delwin(window);
    endwin();
    return 0;
}
