#include <ncurses.h>

#include "MainMenu/MainMenu.h"

void InitColors() {
  init_color(1, 444, 444, 444);
  init_color(2, 600, 0, 0);
  init_color(3, 0, 0, 0);
  init_pair(1, 1, COLOR_BLACK);
  init_pair(15, 2, 3);
}

int main() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  start_color();
  InitColors();

  MainMenuCycle();
  endwin();
  return 0;
}
