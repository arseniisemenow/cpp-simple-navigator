#include "DepthAndBreadthFirstSearchMenu.h"

#include <ncurses.h>

#include "GraphAlgorithms/GraphAlgorithms.h"

void DepthAndBreadthFirstSearchMenuCycle(
    const std::vector<std::string> &graphs) {
  s21::GraphAlgorithms graph_algorithms{};
  s21::Graph graph{};

  int selected_graph_index = 0;
  std::string start_index_input;
  bool running = true;

  while (running) {
    clear();
    mvprintw(0, 0, "DFS/BFS Algorithm Menu");
    mvprintw(2, 0, "Select Graph:");

    int row, col;
    getmaxyx(stdscr, row, col);

    // Create a window for the file path selection UI
    mvprintw(row - 2, 0, "Use number key to input the number");
    mvprintw(row - 1, 0, "Use Backspace to correct the number");

    // List all graphs with their names
    for (size_t i = 0; i < graphs.size(); ++i) {
      if (i == selected_graph_index) {
        attron(A_REVERSE);
      }
      mvprintw(3 + i, 2, graphs[i].c_str());
      if (i == selected_graph_index) {
        attroff(A_REVERSE);
      }
    }

    mvprintw(3 + graphs.size() + 1, 0, "Enter start index: ");
    mvprintw(3 + graphs.size() + 1, 18, start_index_input.c_str());
    mvprintw(3 + graphs.size() + 2, 0, "Press 's' to start DFS.");
    mvprintw(3 + graphs.size() + 3, 0, "Press 'b' to start BFS.");
    mvprintw(3 + graphs.size() + 4, 0, "Press 'q' to return to the main menu.");

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
      case KEY_BACKSPACE:
      case 127:
        if (!start_index_input.empty()) {
          start_index_input.pop_back();
        }
        break;
      case 10:  // Enter key
        break;
      case 's':
        if (start_index_input.empty()) {
          clear();
          mvprintw(0, 0, "start index must be not empty");
          getch();
        } else {
          const int start_index = std::stoi(start_index_input);
          clear();
          graph.LoadGraphFromFile(graphs[selected_graph_index]);
          auto dfs_result =
              graph_algorithms.DepthFirstSearch(graph, start_index);

          mvprintw(0, 0, "Depth First Search Result:");
          for (size_t i = 0; i < dfs_result.size(); ++i) {
            mvprintw(2 + i, 2, "%d", dfs_result[i]);
          }
          graph.Clear();
          getch();
        }
        break;
      case 'b':
        if (start_index_input.empty()) {
          clear();
          mvprintw(0, 0, "start index must be not empty");
          getch();
        } else {
          const int start_index = std::stoi(start_index_input);
          clear();
          graph.LoadGraphFromFile(graphs[selected_graph_index]);
          auto bfs_result =
              graph_algorithms.BreadthFirstSearch(graph, start_index);

          mvprintw(0, 0, "Breadth First Search Result:");
          for (size_t i = 0; i < bfs_result.size(); ++i) {
            mvprintw(2 + i, 2, "%d", bfs_result[i]);
          }
          graph.Clear();
          getch();
        }
        break;
      case 'q':
        running = false;
        break;
      default:
        if (isdigit(ch)) {
          if (start_index_input.length() < 5) {
            start_index_input += ch;
          }
        }
        break;
    }
  }
}
