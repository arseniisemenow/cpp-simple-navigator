#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SEARCHENGINE_SEARCHENGINE_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SEARCHENGINE_SEARCHENGINE_H_

#include <iostream>

#include "Graph/Graph.h"

namespace s21 {

class SearchEngine {
 public:
  [[nodiscard]] std::vector<int> DepthFirstSearch(const Graph &graph,
                                                  const int start_index);
  [[nodiscard]] std::vector<int> BreadthFirstSearch(const Graph &graph,
                                                    const int start_index);
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SEARCHENGINE_SEARCHENGINE_H_
