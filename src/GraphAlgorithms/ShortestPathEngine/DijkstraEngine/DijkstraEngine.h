#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SHORTESTPATHENGINE_DIJKSTRAENGINE_DIJKSTRAENGINE_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SHORTESTPATHENGINE_DIJKSTRAENGINE_DIJKSTRAENGINE_H_

#include "Graph/Graph.h"
#include <limits>

namespace s21 {
class DijkstraEngine {
 public:
    [[nodiscard]] int GetShortestPathBetweenVertices(const Graph &graph, int vertex_1, int vertex_2);

 private:
    inline const static int kInfinity = std::numeric_limits<int>::max();
};
}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SHORTESTPATHENGINE_DIJKSTRAENGINE_DIJKSTRAENGINE_H_
