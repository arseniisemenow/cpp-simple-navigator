#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SHORTESTPATHENGINE_SHORTESTPATHENGINE_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SHORTESTPATHENGINE_SHORTESTPATHENGINE_H_

#include "Graph/Graph.h"
#include "GraphAlgorithms/ShortestPathEngine/DijkstraEngine/DijkstraEngine.h"
#include "GraphAlgorithms/ShortestPathEngine/FloydWarshallEngine/FloydWarshallEngine.h"

namespace s21 {
class ShortestPathEngine {
 public:
  /* Dijkstra's algorithm */
  [[nodiscard]] int GetShortestPathBetweenVertices(const Graph &graph,
                                                   int vertex_1, int vertex_2);
  /* Floyd-Warshall algorithm */
  [[nodiscard]] std::vector<std::vector<int>>
  GetShortestPathsBetweenAllVertices(const Graph &);

 private:
  DijkstraEngine dijkstra_engine_;
  FloydWarshallEngine floyd_warshall_engine_;
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_SHORTESTPATHENGINE_SHORTESTPATHENGINE_H_
