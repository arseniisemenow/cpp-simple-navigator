#include "GraphAlgorithms.h"

namespace s21 {
std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph &graph, int start_index) {
    return search_engine_.DepthFirstSearch(graph, start_index);
}
std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph &graph, int start_index) {
    return search_engine_.BreadthFirstSearch(graph, start_index);
}
int GraphAlgorithms::GetShortestPathBetweenVertices(const Graph &graph, int vertex_1, int vertex_2) {
    return shortest_path_engine_.GetShortestPathBetweenVertices(graph, vertex_1, vertex_2);
}
std::vector<std::vector<int>> GraphAlgorithms::GetShortestPathsBetweenAllVertices(const Graph &graph) {
    return shortest_path_engine_.GetShortestPathsBetweenAllVertices(graph);
}
std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(const Graph &graph) {
    return least_spanning_tree_engine_.GetLeastSpanningTree(graph);
}
TspResult GraphAlgorithms::SolveTravelingSalesmanProblem(const Graph &graph, const AlgorithmType algorithm_type) {
    if (algorithm_type == kColonyAlgorithm) {
        return colony_algorithm_.SolveTravelingSalesmanProblem(graph);
    }
    if (algorithm_type == kBrutForceAlgorithm) {
        return  brut_force_algorithm_.SolveTravelingSalesmanProblem(graph);
    }
    if (algorithm_type == kAlgorithm1) {
        return algorithm_1_.SolveTravelingSalesmanProblem(graph);
    }
    if (algorithm_type == kAlgorithm2) {
        return algorithm_2_.SolveTravelingSalesmanProblem(graph);
    }
    return {};
}

}// namespace s21