#include "TSPComparisonMode.h"

#include <ncurses.h>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "GraphAlgorithms/GraphAlgorithms.h"

const char *AlgorithmTypeToString(const s21::AlgorithmType type) {
    switch (type) {
        case s21::AlgorithmType::kColonyAlgorithm: return "Ant Colony Algorithm";
        case s21::AlgorithmType::kBrutForceAlgorithm: return "Brute Force Algorithm";
        case s21::AlgorithmType::kHeldKarpAlgorithm: return "Held-Karp Algorithm";
        case s21::AlgorithmType::kGeneticAlgorithm: return "Genetic Algorithm";
        default: return "Unknown Algorithm";
    }
}

void ShowLoadingIndicator(int row, std::atomic<bool> &running) {
    const char *animation = "|/-\\";
    int i = 0;
    while (running) {
        mvprintw(row, 40, "%c", animation[i % 4]);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ++i;
    }
}

void TSPComparisonMode(const std::vector<std::string> &graphs) {
    s21::GraphAlgorithms graph_algorithms{};
    s21::Graph graph{};

    int selected_graph_index = 0;
    std::vector<s21::AlgorithmType> selected_algorithms;
    bool running = true;
    bool start = false;

    while (running) {
        clear();
        mvprintw(0, 0, "TSP Comparison Mode");
        mvprintw(2, 0, "Select Graph:");

        int row, col;
        getmaxyx(stdscr, row, col);

        for (size_t i = 0; i < graphs.size(); ++i) {
            if (i == selected_graph_index) {
                attron(A_REVERSE);
            }
            mvprintw(3 + i, 2, graphs[i].c_str());
            if (i == selected_graph_index) {
                attroff(A_REVERSE);
            }
        }

        mvprintw(3 + graphs.size() + 1, 0, "Toggle Algorithms (Press numbers to toggle):");

        std::vector<s21::AlgorithmType> all_algorithms = {
            s21::AlgorithmType::kColonyAlgorithm,
            s21::AlgorithmType::kBrutForceAlgorithm,
            s21::AlgorithmType::kHeldKarpAlgorithm,
            s21::AlgorithmType::kGeneticAlgorithm
        };

        for (size_t i = 0; i < all_algorithms.size(); ++i) {
            bool selected = std::find(selected_algorithms.begin(), selected_algorithms.end(), all_algorithms[i]) != selected_algorithms.end();
            if (selected) {
                attron(A_BOLD);
            }
            mvprintw(3 + graphs.size() + 2 + i, 2, "%d. %s", i + 1, AlgorithmTypeToString(all_algorithms[i]));
            if (selected) {
                attroff(A_BOLD);
            }
        }

        mvprintw(3 + graphs.size() + 7, 0, "Press 's' to start the algorithms.");
        mvprintw(3 + graphs.size() + 8, 0, "Press 'q' to return to the main menu.");

        int ch = getch();
        switch (ch) {
            case KEY_UP:
                if (selected_graph_index > 0) {
                    --selected_graph_index;
                }
                break;
            case KEY_DOWN:
                if (selected_graph_index < static_cast<int>(graphs.size()) - 1) {
                    ++selected_graph_index;
                }
                break;
            case '1':
            case '2':
            case '3':
            case '4': {
                int index = ch - '1';
                if (index >= 0 && index < static_cast<int>(all_algorithms.size())) {
                    s21::AlgorithmType selected_algorithm = all_algorithms[index];
                    auto it = std::find(selected_algorithms.begin(), selected_algorithms.end(), selected_algorithm);
                    if (it != selected_algorithms.end()) {
                        selected_algorithms.erase(it);
                    } else {
                        selected_algorithms.push_back(selected_algorithm);
                    }
                }
                break;
            }
            case 's':
                if (selected_algorithms.empty()) {
                    clear();
                    mvprintw(0, 0, "You must select at least one algorithm.");
                    getch();
                } else {
                    start = true;
                    running = false;
                }
                break;
            case 'q':
                running = false;
                break;
        }
    }

    if (start) {
        std::vector<std::thread> threads;
        std::vector<std::atomic<bool>> running_flags(selected_algorithms.size());
        std::vector<s21::TspResult> results(selected_algorithms.size());
        std::vector<std::chrono::duration<double>> durations(selected_algorithms.size());

        graph.LoadGraphFromFile(graphs[selected_graph_index]);

        for (size_t i = 0; i < selected_algorithms.size(); ++i) {
            running_flags[i] = true;
            threads.emplace_back([&, i]() {
                std::atomic<bool> &running = running_flags[i];
                std::thread loading_thread(ShowLoadingIndicator, 3 + graphs.size() + 2 + i, std::ref(running));

                auto start_time = std::chrono::high_resolution_clock::now();
                results[i] = graph_algorithms.SolveTravelingSalesmanProblem(graph, selected_algorithms[i]);
                auto end_time = std::chrono::high_resolution_clock::now();

                durations[i] = end_time - start_time;
                running = false;
                loading_thread.join();
            });
        }

        for (auto &thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }

        clear();
        mvprintw(0, 0, "TSP Comparison Results:");

        int result_row = 2;
        mvprintw(result_row, 0, "Algorithm                 Time (s)   Distance");
        result_row++;
        mvprintw(result_row, 0, "-------------------------------------------------");
        result_row++;

        for (size_t i = 0; i < selected_algorithms.size(); ++i) {
            std::ostringstream time_stream;
            time_stream << std::fixed << std::setprecision(2) << durations[i].count();

            mvprintw(result_row, 0, "%-25s %-10s %lf", AlgorithmTypeToString(selected_algorithms[i]), time_stream.str().c_str(), results[i].distance);
            result_row++;
        }

        getch();
    }
}
