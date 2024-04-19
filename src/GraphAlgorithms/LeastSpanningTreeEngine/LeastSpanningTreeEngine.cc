#include "LeastSpanningTreeEngine.h"

#include <set>
#include <unordered_set>

#include "common/constants.h"

namespace s21 {

std::pair<std::pair<int, int>, int> GetMinimalEdge(const Graph &graph, const std::set<int> &visited) {
    std::pair<int, int> minimal_edge{};
    minimal_edge.first = 0;
    minimal_edge.second = 0;
    int cost = constants::kInfinity;
    if (visited.empty()) {
        for (int i = 0; i < graph.GetSize(); ++i) {
            for (int j = 0; j < graph.GetSize(); ++j) {
                if (graph.GetDistance(i, j) < cost) {
                    cost = graph.GetDistance(i, j);
                    minimal_edge = {i, j};
                }
            }
        }
        return {minimal_edge, cost};
    }

    for (int i = 0; i < graph.GetSize(); ++i) {
        if (visited.find(i) != visited.end()) {
            for (int j = 0; j < graph.GetSize(); ++j) {
                if (i == j || visited.find(j) != visited.end()) {
                    continue;
                }
                if (graph.GetDistance(i, j) < cost) {
                    minimal_edge.first = i;
                    minimal_edge.second = j;
                    cost = graph.GetDistance(i, j);
                }
            }
        }
    }
    return {minimal_edge, cost};
}

[[nodiscard]] std::vector<std::vector<int>> LeastSpanningTreeEngine::GetLeastSpanningTree(const Graph &graph) {
    std::vector<std::vector<int>> least_spanning_tree(graph.GetSize(), std::vector<int>(graph.GetSize(), {}));
    std::set<int> visited{};

    for (int i = 0; i < graph.GetSize() - 1; ++i) {
        const auto minimal_edge_with_cost = GetMinimalEdge(graph, visited);
        const auto minimal_edge = minimal_edge_with_cost.first;
        const auto cost = minimal_edge_with_cost.second;
        if (cost == constants::kInfinity) {
            break;
        }
        least_spanning_tree[minimal_edge.first][minimal_edge.second] = cost;
        least_spanning_tree[minimal_edge.second][minimal_edge.first] = cost;
        visited.insert(minimal_edge.first);
        visited.insert(minimal_edge.second);
    }

    return least_spanning_tree;
}
}// namespace s21