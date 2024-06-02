#include "MainMenu.h"

#include <filesystem>
#include "cli/ItemOneMenu/ItemOneMenu.h"
#include "cli/ItemTwoMenu/ItemTwoMenu.h"
#include "cli/ItemFourMenu/ItemFourMenu.h"
#include "cli/LeastSpanningTreeMenu/LeastSpanningTreeMenu.h"

#include "cli/common/constants.h"
#include "cli/ChooseFilePath/ChooseFilePath.h"
#include "Graph/Graph.h"
#include "GraphAlgorithms/GraphAlgorithms.h"

int MainMenuCycle() {
  const std::vector<MenuItem> select_menu_items = {
      {"Update Dataset Path", false},
      {"Depth And Breadth First Search", false},
      {"Find The Shortest Path Between Vertices", false},
      {"Find Least Spanning Tree", false},
      {"Travelling Salesman Problem", false},
      {"Exit", false}};
  std::string dataset_path = GetCurrentWorkingDirectory();
  std::vector<std::string> graphs;

  int selected_index = 0;
  int c;
  while (true) {
    DrawMainMenu(select_menu_items, selected_index, dataset_path);

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
          graphs.clear();
          for (const auto &entry : std::filesystem::directory_iterator(dataset_path)) {
            if (entry.is_regular_file()) {
              graphs.push_back(entry.path().string());
            }
          }
          continue;
        }
        if (select_menu_items[selected_index].label == select_menu_items[select_menu_items.size() - 1].label) {
          endwin();
          return 0;
        } else {
          clear();
          if (selected_index == s21::constants::cli::kMenuItem1Index) {
            ItemOneMenuCycle(graphs);
            continue;
          }
          if (selected_index == s21::constants::cli::kMenuItem2Index) {
            ItemTwoMenuCycle(graphs);
            continue;
          }
          if (selected_index == s21::constants::cli::kMenuItem3Index) {
            LeastSpanningTreeMenuCycle(graphs);
            continue;
          }
          if (selected_index == s21::constants::cli::kMenuItem4Index) {
            ItemFourMenuCycle();
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
