#include "ShortestPathEngine.h"

namespace s21{

[[nodiscard]] int ShortestPathEngine::GetShortestPathBetweenVertices(const Graph &graph, int vertex_1, int vertex_2){
    return dijkstra_engine_.GetShortestPathBetweenVertices(graph, vertex_1, vertex_2);
}

[[nodiscard]] std::vector<std::vector<int>> ShortestPathEngine::GetShortestPathsBetweenAllVertices(const Graph& graph){
    return floyd_warshall_engine_.GetShortestPathsBetweenAllVertices(graph);
}
}
