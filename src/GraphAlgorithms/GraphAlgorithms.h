#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_GRAPHALGORITHMS_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_GRAPHALGORITHMS_H_

#include <array>

#include "Graph/Graph.h"
#include "Vertex/Vertex.h"

namespace s21 {

class GraphAlgorithms {
 public:
    [[nodiscard]] std::vector<Vertex> DepthFirstSearch(const Graph &graph, int start_index);
    [[nodiscard]] std::vector<Vertex> BreadthFirstSearch(const Graph &graph, int start_index);
    [[nodiscard]] int GetShortestPathBetweenVertices(const Graph &graph, int vertex_1, int vertex_2);
    GetShortestPathsBetweenAllVertices
 private:
    Graph graph_{};
};

}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_GRAPHALGORITHMS_H_
