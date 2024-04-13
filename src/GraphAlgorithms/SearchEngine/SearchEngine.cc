#include "SearchEngine.h"

namespace s21 {

std::vector<int> SearchEngine::DepthFirstSearch(const Graph &graph, int start_index) {
    if (start_index >= graph.GetGraph().size()) {
        return {};
    }
    std::vector<int> result;
    std::unordered_set<int> visited;
    SearchUtility(graph, start_index - 1, result, visited);
    return result;
}

void SearchEngine::SearchUtility(const Graph &graph, int vertex, std::vector<int> &result, std::unordered_set<int> &visited) const {
    visited.insert(vertex);
    result.push_back(vertex + 1);

    for (size_t i = 0; i < graph.GetGraph().size(); ++i) {
        if (graph.GetGraph()[vertex][i] != 0 && visited.find(i) == visited.end()) {
            SearchUtility(graph, i, result, visited);
        }
    }
}

std::vector<int> SearchEngine::BreadthFirstSearch(const Graph &graph, int start_index) {
    if (start_index >= graph.GetGraph().size()) {
        return {};
    }
    std::vector<int> result;
    std::unordered_set<int> visited;
    List<int> queue;
    queue.push_back(start_index - 1);
    visited.insert(start_index - 1);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop_front();
        result.push_back(current + 1);

        for (size_t i = 0; i < graph.GetGraph().size(); ++i) {
            if (graph.GetGraph()[current][i] != 0 && visited.find(i) == visited.end()) {
                queue.push_back(i);
                visited.insert(i);
            }
        }
    }

    return result;
}
}// namespace s21
