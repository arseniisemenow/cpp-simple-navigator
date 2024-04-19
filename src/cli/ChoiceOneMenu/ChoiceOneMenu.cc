#include "ChoiceOneMenu.h"

#include <chrono>// for std::chrono
#include <mutex> // for std::mutex
#include <thread>// for std::thread
#include <vector>

#include "../../common/multithread.h"
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
    if (progress != 100) {
        mvprintw(y, x + width + 2, "[RUNNING]");
    }else {
        mvprintw(y, x + width + 2, "[FINISHED]");
    }
}

void UpdateProgressBar1() {
    while (s21::multithread::stop_thread_1 == false) {
        if (s21::multithread::calculate_thread_1) {
            std::lock_guard<std::mutex> lock(s21::multithread::mutex_1);

            s21::multithread::progress_1 = (s21::multithread::progress_1 + 1);

            if (s21::multithread::progress_1 == 100) {
                // s21::multithread::stop_thread_1 = true;
                s21::multithread::calculate_thread_1 = false;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

void UpdateProgressBar2() {
    while (s21::multithread::stop_thread_2 == false) {
        if (s21::multithread::calculate_thread_2) {
            std::lock_guard<std::mutex> lock(s21::multithread::mutex_2);

            //todo: update progress_2 value

            s21::multithread::progress_2 = (s21::multithread::progress_2 + 1);

            if (s21::multithread::progress_2 == 100) {
                // s21::multithread::stop_thread_2 = true;
                s21::multithread::calculate_thread_2 = false;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

// Function to draw the user interface
void DrawInterface() {
    while (s21::multithread::stop_thread_1 == false && s21::multithread::stop_thread_2 == false) {
        // Clear the screen
        clear();

        // Draw menu
        DrawMenu(menu_items, selected_index);

        // Draw progress bars
        DrawProgressBar(5, 0, 40, s21::multithread::progress_1);
        DrawProgressBar(7, 0, 40, s21::multithread::progress_2);

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

    int c;
    while (true) {

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
                    s21::multithread::stop_thread_1 = true;
                    s21::multithread::stop_thread_2 = true;

                    progress_thread_1.join();
                    progress_thread_2.join();
                    interface_thread.join();
                    return 0;
                }
                clear();
                if (selected_index == 0) {
                    s21::multithread::calculate_thread_1 = true;
                    s21::multithread::calculate_thread_2 = true;
                }

                //todo: call from here another menus
                refresh();
                // getch();// Wait for user to press any key
                break;
            default:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                ;
        }
    }
}
