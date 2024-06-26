#include "ItemTwoMenu.h"

#include <vector>

#include "cli/ShortestPathBetweenAllVerticesMenu/ShortestPathBetweenAllVerticesMenu.h"
#include "cli/ShortestPathBetweenVerticesMenu/ShortestPathBetweenVerticesMenu.h"

#include "cli/common/constants.h"
#include "cli/common/structs.h"

int ItemTwoMenuCycle(const std::vector<std::string> &graphs) {
    const std::vector<MenuItem> select_menu_items = {
        {"Get Shortest Path Between Vertices", false},
        {"Get Shortest Path Between All Vertices", false},
        {"Go Back", false}};

    int selected_index = 0;
    int c;
    while (true) {
        DrawSubMenu(select_menu_items, selected_index);

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
                if (select_menu_items[selected_index].label == select_menu_items[select_menu_items.size() - 1].label) {
                    endwin();
                    return 0;
                }
                clear();
                if (selected_index == s21::constants::cli::item_2::kMenuItem1Index) {
                    ShortestPathBetweenVerticesMenuCycle(graphs);
                    continue;
                }
                if (selected_index == s21::constants::cli::item_2::kMenuItem2Index) {
                    ShortestPathBetweenAllVerticesMenuCycle(graphs);
                }
                //          refresh();
                getch();// Wait for user to press any key

                break;
        }
    }
}