#include "MainMenu.h"

#include "cli/ChoiceOneMenu/ChoiceOneMenu.h"
#include "cli/common/constants.h"
#include "cli/ChooseFilePath/ChooseFilePath.h"

int MainMenuCycle() {

  const std::vector<MenuItem> select_menu_items = {
      {"Update Dataset Path", false},
      {"Depth And Breadth First Search", false},
      {"Find The Shortest Path Between Vertices", false},
      {"Find Least Spanning Tree", false},
      {"Travelling Salesman Problem", false},
      {"Exit", false}};

  std::string dataset_path = GetCurrentWorkingDirectory();

  int selected_index = 0;
  int c;
  while (true) {
    DrawMenu(select_menu_items, selected_index, dataset_path);

    c = getch();
    switch (c) {
      case KEY_UP:
        if (selected_index > 0)
          --selected_index;
        break;
      case KEY_DOWN:
        if (selected_index < static_cast<int>(select_menu_items.size()) - 1)
          ++selected_index;
        break;
      case 10:// Enter key
        if (selected_index == s21::constants::cli::kDatasetPathIndex) {
          ChooseFilePath(dataset_path);
          continue;
        }
        if (select_menu_items[selected_index].label == "Exit") {
          endwin();
          return 0;
        } else {
          clear();
          if (selected_index == s21::constants::cli::kMenuItem1Index) {
            ChoiceOneMenu();
            continue;
          }
          if (selected_index == s21::constants::cli::kMenuItem2Index) {
            continue;
          }
          if (selected_index == s21::constants::cli::kMenuItem3Index) {
            continue;
          }
          if (selected_index == s21::constants::cli::kMenuItem4Index) {
            continue;
          }
//          //todo: call from here another menus
//          refresh();
//          // getch();// Wait for user to press any key
        }
        break;
    }
  }
}
