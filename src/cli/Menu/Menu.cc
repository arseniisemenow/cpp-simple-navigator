#include "Menu.h"

void DrawMenu(const std::vector<MenuItem> &items, const int selected_index, const std::string &dataset_path) {
  clear();

  mvprintw(0, 0, "Dataset Path: %s", dataset_path.c_str());

  for (size_t i = 0; i < items.size(); ++i) {
    if (i == selected_index) {
      attron(A_REVERSE);
      mvprintw(i + 2, 1, "%s", items[i].label.c_str());
      attroff(A_REVERSE);
    } else {
      mvprintw(i + 2, 1, "%s", items[i].label.c_str());
    }
  }
  refresh();
}

