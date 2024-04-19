#include "MainMenu.h"

#include "cli/ChoiceOneMenu/ChoiceOneMenu.h"
#include "cli/common/constants.h"
#include "common/constants.h"

int MainMenuCycle() {
    const std::vector<MenuItem> menu_items = {
        {"Choice 1", false},
        {"Choice 2", false},
        {"Choice 3", false},
        {"Choice 4", false},
        {"Exit", false}};

    int selected_index = 0;
    int c;
    while (true) {
        s21::multithread::stop_thread = false;
        s21::multithread::calculate = false;
        s21::multithread::progress1 = 0;
        s21::multithread::progress2 = 0;

        DrawMenu(menu_items, selected_index);
        c = getch();
        switch (c) {
            case KEY_UP:
                if (selected_index > 0)
                    --selected_index;
                break;
            case KEY_DOWN:
                if (selected_index < static_cast<int>(menu_items.size()) - 1)
                    ++selected_index;
                break;
            case 10:// Enter key
                if (menu_items[selected_index].label == "Exit") {
                    endwin();
                    return 0;
                } else {
                    // Perform action for selected menu item
                    clear();
                    mvprintw(0, 0, "You chose %s", menu_items[selected_index].label.c_str());
                    if (selected_index == 0) {
                        ChoiceOneMenu();
                        continue;
                    }
                    //todo: call from here another menus
                    refresh();
                    getch();// Wait for user to press any key
                }
                break;
        }
    }
}
