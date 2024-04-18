#include "DijkstraEngine.h"

#include "containers/adaptors/Queue/Queue.h"
#include <limits>
#include <vector>

namespace s21 {

int DijkstraEngine::GetShortestPathBetweenVertices(const Graph &graph, int vertex_1, int vertex_2) {
    vertex_1 -= 1;
    vertex_2 -= 1;
    if (vertex_1 < 0 || vertex_2 < 0 || vertex_1 >= graph.GetGraph().size() || vertex_2 >= graph.GetGraph().size()) {
        return 0;
    }

    std::vector<std::vector<int>> adjacency_matrix = graph.GetGraph();



    return kInfinity;
}
}// namespace s21
