#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

#include <vector>

#include "cli/common/structs.h"

void DrawMenu(const std::vector<MenuItem> &items, const int selected_index, const std::string &dataset_path);


#endif //MENU_H
