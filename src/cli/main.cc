#include <ncurses.h>
#include <string>
#include <vector>

#include "common/structs.h"
#include "MainMenu/MainMenu.h"

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    MainMenuCycle();
    endwin();
    return 0;
}
