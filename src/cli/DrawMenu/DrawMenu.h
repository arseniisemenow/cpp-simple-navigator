#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_CLI_DRAW_MENU_DRAW_MENU_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_CLI_DRAW_MENU_DRAW_MENU_H_

#include <ncurses.h>

#include <vector>

#include "cli/common/structs.h"

void DrawMainMenu(const std::vector<MenuItem> &items, const int selected_index, const std::string &dataset_path, const std::vector<std::string>&);
void DrawSubMenu(const std::vector<MenuItem> &items, const int selected_index);

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_CLI_DRAW_MENU_DRAW_MENU_H_
