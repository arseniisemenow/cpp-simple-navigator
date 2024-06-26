#include "LeastSpanningTreeMenu.h"

#include "GraphAlgorithms/GraphAlgorithms.h"

void LeastSpanningTreeMenuCycle(const std::vector<std::string> &graphs) {
    s21::GraphAlgorithms graph_algorithms{};
    s21::Graph graph{};

    int selected_graph_index = 0;
    bool running = true;

    while (running) {
        clear();
        mvprintw(0, 0, "Algorithm Menu");
        mvprintw(2, 0, "Select Graph:");

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

        mvprintw(3 + graphs.size() + 1, 0, "Press 's' to start the algorithm.");
        mvprintw(3 + graphs.size() + 2, 0, "Press 'q' to return to the main menu.");

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
            case 'q':
                running = false;
                break;
            case 's':
                clear();
                graph.LoadGraphFromFile(graphs[selected_graph_index]);
                auto least_spanning_tree = graph_algorithms.GetLeastSpanningTree(graph);
                
                for (size_t i = 0; i < least_spanning_tree.size(); ++i) {
                    for (size_t j = 0; j < least_spanning_tree[i].size(); ++j) {
                        mvprintw(3 + i, 2 + j * 4, "%d", least_spanning_tree[i][j]);
                    }
                }
                graph.Clear();
                getch();
                break;
        }
    }
}
