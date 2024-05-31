#include "ItemOneMenu.h"

#include <vector>

#include "cli/common/constants.h"
#include "cli/common/structs.h"

int ItemOneMenuCycle() {

    const std::vector<MenuItem> select_menu_items = {
        {"Depth First Search", false},
        {"Breadth First Search", false},
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
                } else {
                    clear();
                    if (selected_index == s21::constants::cli::item_1::kMenuItem1Index) {
                        //todo: call another window
                        continue;
                    }
                    if (selected_index == s21::constants::cli::item_1::kMenuItem2Index) {
                        //todo: call another window
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