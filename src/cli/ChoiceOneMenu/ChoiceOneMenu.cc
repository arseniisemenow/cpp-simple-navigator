#include "ChoiceOneMenu.h"

#include <chrono>// for std::chrono
#include <mutex> // for std::mutex
#include <thread>// for std::thread
#include <vector>

#include "cli/common/constants.h"
#include "cli/common/structs.h"
#include "common/constants.h"

const std::vector<MenuItem> menu_items = {
    {"Start", false},
    {"Exit", false}};

int selected_index = 0;

namespace SpecialNamespace {
}// namespace SpecialNamespace

// Function to draw a progress bar
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
}

void UpdateProgressBar1() {
    while (s21::multithread::stop_thread == false) {
        if (s21::multithread::calculate) {
            std::lock_guard<std::mutex> lock(s21::multithread::mtx_1);

            s21::multithread::progress1 = (s21::multithread::progress1 + 1) % 101;

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void UpdateProgressBar2() {
    while (s21::multithread::stop_thread == false) {
        if (s21::multithread::calculate) {
            std::lock_guard<std::mutex> lock(s21::multithread::mtx_2);

            s21::multithread::progress2 = (s21::multithread::progress2 + 2) % 101;

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

// Function to draw the user interface
void DrawInterface() {
    while (s21::multithread::stop_thread == false) {
        // Clear the screen
        clear();

        // Draw menu
        DrawMenu(menu_items, selected_index);

        // Draw progress bars
        DrawProgressBar(5, 0, 40, s21::multithread::progress1);
        DrawProgressBar(7, 0, 40, s21::multithread::progress2);

        // Refresh screen
        refresh();

        // Sleep for a short duration before redrawing
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    clear();
}

int ChoiceOneMenu() {
    std::thread progress_thread_1(UpdateProgressBar1);
    std::thread progress_thread_2(UpdateProgressBar2);
    std::thread interface_thread(DrawInterface);
    // progress_thread.detach();

    int c;
    while (true) {

        // refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
                    // progress_thread.join();
                    s21::multithread::stop_thread = true;

                    progress_thread_1.join();
                    progress_thread_2.join();
                    interface_thread.join();
                    // exit(1);
                    return 0;
                }
                clear();
                if (selected_index == 0) {
                    s21::multithread::calculate = true;
                }

                //todo: call from here another menus
                refresh();
                getch();// Wait for user to press any key
                break;
        }
    }
}
