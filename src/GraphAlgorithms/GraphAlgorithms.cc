#include "GraphAlgorithms.h"

namespace s21 {
std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph &graph, int start_index) {
    return {};
}
std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph &graph, int start_index) {
    return {};
}
int GraphAlgorithms::GetShortestPathBetweenVertices(const Graph &graph, int vertex_1, int vertex_2) {
    return 0;
}
std::vector<std::vector<int>> GraphAlgorithms::GetShortestPathsBetweenAllVertices(const Graph &) {
    return std::vector<std::vector<int>>();
}
std::vector<std::vector<bool>> GraphAlgorithms::GetLeastSpanningTree(const Graph &graph) {
    return std::vector<std::vector<bool>>();
}
TspResult GraphAlgorithms::SolveTravelingSalesmanProblem(const Graph &graph, const AlgorithmType algorithm_type) {
    return TspResult();
}

}// namespace s21