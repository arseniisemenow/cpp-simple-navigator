#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SHORTESTPATHENGINE_DIJKSTRAENGINE_DIJKSTRAENGINE_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SHORTESTPATHENGINE_DIJKSTRAENGINE_DIJKSTRAENGINE_H_

#include <limits>
#include <unordered_set>

#include "Graph/Graph.h"

namespace s21 {
class DijkstraEngine {
 public:
  [[nodiscard]] int GetShortestPathBetweenVertices(const Graph& graph,
                                                   int vertex_1, int vertex_2);

 private:
  [[nodiscard]] int GetCurrentMinimalIndex(
      const std::vector<int>& distances,
      const std::unordered_set<int>& visited) const;
  void UpdateDistances(const Graph& graph, int current_vertex,
                       std::vector<int>& updated_distances,
                       const std::unordered_set<int>& visited) const;

 private:
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SHORTESTPATHENGINE_DIJKSTRAENGINE_DIJKSTRAENGINE_H_
