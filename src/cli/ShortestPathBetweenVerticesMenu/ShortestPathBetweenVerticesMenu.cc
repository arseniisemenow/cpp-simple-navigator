#include "ShortestPathBetweenVerticesMenu.h"

#include "GraphAlgorithms/GraphAlgorithms.h"

void ShortestPathBetweenVerticesMenuCycle(
    const std::vector<std::string> &graphs) {
  s21::GraphAlgorithms graph_algorithms{};
  s21::Graph graph{};

  int selected_graph_index = 0;
  std::string start_index_input;
  std::string finish_index_input;
  bool running = true;

  while (running) {
    clear();
    mvprintw(0, 0, "Shortest Path Algorithm Menu");
    mvprintw(2, 0, "Select Graph:");

    int row, col;
    getmaxyx(stdscr, row, col);

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
    mvprintw(3 + graphs.size() + 2, 0, "Enter finish index: ");
    mvprintw(3 + graphs.size() + 2, 19, finish_index_input.c_str());
    mvprintw(3 + graphs.size() + 3, 0, "Press 's' to find the shortest path.");
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
        if (start_index_input.empty() && !finish_index_input.empty()) {
          finish_index_input.pop_back();
        } else if (!start_index_input.empty()) {
          start_index_input.pop_back();
        }
        break;
      case 10:  // Enter key
        break;
      case 's':
        if (start_index_input.empty() || finish_index_input.empty()) {
          clear();
          mvprintw(0, 0, "Both start and finish indices must be provided");
          getch();
        } else {
          const int start_index = std::stoi(start_index_input);
          const int finish_index = std::stoi(finish_index_input);
          clear();
          graph.LoadGraphFromFile(graphs[selected_graph_index]);
          int shortest_path = graph_algorithms.GetShortestPathBetweenVertices(
              graph, start_index, finish_index);

          mvprintw(0, 0, "Shortest Path Result:");
          mvprintw(2, 2, "From %d to %d: %d", start_index, finish_index,
                   shortest_path);
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
          } else if (finish_index_input.length() < 5) {
            finish_index_input += ch;
          }
        }
        break;
    }
  }
}
