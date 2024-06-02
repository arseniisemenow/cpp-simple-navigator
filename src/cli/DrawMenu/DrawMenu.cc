#include "DrawMenu.h"

#include "Graph/Graph.h"
#include "cli/ParseDatasetPath/ParseDatasetPath.h"

void DrawMainMenu(std::vector<MenuItem> items, const int selected_index,
                  const std::string &dataset_path, const std::vector<std::string> &graphs) {
    clear();
    std::string path_error;
    std::string algorithm_error;

    if (graphs.empty()) {
        path_error = " - no txt files inside!";
        algorithm_error = " - unavailable";
    }
    for (int i = 1; i < items.size() && i <= 4; ++i) {
        items[i].label += algorithm_error;
    }
    if (graphs.empty())
        attron(COLOR_PAIR(15));
    mvprintw(0, 0, "Dataset Path: %s%s", dataset_path.c_str(), path_error.c_str());
    if (graphs.empty())
        attroff(COLOR_PAIR(15));

    for (size_t i = 0; i < items.size(); ++i) {
        if (i == selected_index) {
            attron(A_REVERSE);
            mvprintw(i + 2, 1, "%s", items[i].label.c_str());
            attroff(A_REVERSE);
        } else {
            if (graphs.empty() && (i <= 4 && i > 0)) {
                attron(COLOR_PAIR(1));
                mvprintw(i + 2, 1, "%s", items[i].label.c_str());
                attroff(COLOR_PAIR(1));
            } else {
                mvprintw(i + 2, 1, "%s", items[i].label.c_str());
            }
        }
    }

    mvprintw(3 + graphs.size() + 8, 0, "Press 'Enter' to enter the algorithm.");
    mvprintw(3 + graphs.size() + 9, 0, "Press 'Exit' to exit.");

    refresh();
}

void DrawSubMenu(const std::vector<MenuItem> &items, const int selected_index) {
    clear();

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
