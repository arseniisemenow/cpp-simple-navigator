#include "DrawMenu.h"

#include "Graph/Graph.h"
#include "cli/ParseDatasetPath/ParseDatasetPath.h"

void DrawMainMenu(const std::vector<MenuItem> &items, const int selected_index,
    const std::string &dataset_path, const std::vector<std::string> &graphs) {
    clear();

    mvprintw(0, 0, "Dataset Path: %s", dataset_path.c_str());
    if (graphs.empty()) {
    mvprintw(1, 0, "Dataset Path does NOT contain any txt files!", dataset_path.c_str());

    }

    start_color();
    init_color(1, 444, 444, 444);
    init_pair(1, 1, COLOR_BLACK);

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
