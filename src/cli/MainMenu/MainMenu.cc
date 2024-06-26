#include "MainMenu.h"

#include <filesystem>

#include "Graph/Graph.h"
#include "cli/ChooseFilePath/FilePathHandler.h"
#include "cli/DepthAndBreadthFirstSearchMenu/DepthAndBreadthFirstSearchMenu.h"
#include "cli/ItemTwoMenu/ItemTwoMenu.h"
#include "cli/LeastSpanningTreeMenu/LeastSpanningTreeMenu.h"
#include "cli/ParseDatasetPath/ParseDatasetPath.h"
#include "cli/TSPComparisonMode/TSPComparisonMode.h"
#include "cli/common/constants.h"
#include "common/structs.h"

int MainMenuCycle() {
    std::vector<MenuItem> select_menu_items = {
        {"Update Dataset Path", false},
        {"Depth And Breadth First Search", false},
        {"Find The Shortest Path Between Vertices", false},
        {"Find Least Spanning Tree", false},
        {"Travelling Salesman Problem", false},
        {"Exit", false}};
    std::string dataset_path = GetCurrentWorkingDirectory();
    dataset_path = FindDatasetDirectory(dataset_path);
    std::vector<std::string> graphs{};
    ParseDatasetPath(dataset_path, graphs);

    int selected_index = 0;
    int c;
    while (true) {
        DrawMainMenu(select_menu_items, selected_index, dataset_path, graphs);
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
                    ParseDatasetPath(dataset_path, graphs);
                    continue;
                }
                if (select_menu_items[selected_index].label == select_menu_items[select_menu_items.size() - 1].label) {
                    endwin();
                    return 0;
                }
                clear();
                if (!graphs.empty()) {
                    if (selected_index == s21::constants::cli::kMenuItem1Index) {
                        DepthAndBreadthFirstSearchMenuCycle(graphs);
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
                        int selected_graph_index = 0;
                        std::vector<s21::AlgorithmType> selected_algorithms;
                        int num_runs = 1;
                        TSPComparisonMode(std::ref(graphs), selected_graph_index, selected_algorithms, num_runs);
                        continue;
                    }
                }
                //          // getch();// Wait for user to press any key
                break;
        }
    }
}
