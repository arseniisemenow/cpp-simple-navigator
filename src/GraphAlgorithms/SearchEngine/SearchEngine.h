#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SEARCHENGINE_SEARCHENGINE_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SEARCHENGINE_SEARCHENGINE_H_

#include <iostream>
#include <unordered_set>

#include "Graph/Graph.h"
#include "containers/adaptors/Queue/Queue.h"

namespace s21 {

class SearchEngine {
 public:
    [[nodiscard]] std::vector<int> DepthFirstSearch(const Graph &graph, int start_index);
    [[nodiscard]] std::vector<int> BreadthFirstSearch(const Graph &graph, int start_index);
 private:
    void SearchUtility(const Graph &graph, int vertex, std::vector<int> &result, std::unordered_set<int> &visited) const;
};
}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SEARCHENGINE_SEARCHENGINE_H_
