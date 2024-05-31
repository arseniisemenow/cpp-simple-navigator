#include "ChoiceOneMenu.h"

#include <vector>

#include "cli/common/structs.h"
#include "common/constants.h"

const std::vector<MenuItem> menu_items = {
    {"Start", false},
    {"Exit", false}};

int selected_index = 0;

void DrawProgressBar(int y, int x, int width, int progress) {
    mvprintw(y, x, "[");
    int pos = 1;
    for (int i = 0; i < width; ++i) {
        if (i < progress * width / 100) {
            mvprintw(y, x + pos++, "=");
        } else {
            mvprintw(y, x + pos++, " ");
        }
    }
    printw("]");
    if (progress != 100) {
        mvprintw(y, x + width + 2, "[RUNNING]");
    }else {
        mvprintw(y, x + width + 2, "[FINISHED]");
    }
}

int ChoiceOneMenu() {
    int c;
    while (true) {

        c = getch();
        switch (c) {
            case KEY_UP:
                if (selected_index > 0) { --selected_index; }
                break;
            case KEY_DOWN:
                if (selected_index < static_cast<int>(menu_items.size()) - 1)
                    ++selected_index;
                break;
            case 10:// Enter key
                if (menu_items[selected_index].label == "Exit") {
                    return 0;
                }
                clear();
                if (selected_index == 0) {
                }

                //todo: call from here another menus
                refresh();
                // getch();// Wait for user to press any key
                break;
            default:;
        }
    }
}