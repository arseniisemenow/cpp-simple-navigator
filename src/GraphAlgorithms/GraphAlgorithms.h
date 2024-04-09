#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_GRAPHALGORITHMS_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_GRAPHALGORITHMS_H_

#include <array>

#include "Graph/Graph.h"
#include "Vertex/Vertex.h"
#include "common/structs.h"
#include "GraphAlgorithms/TSPAlgorithms/Algorithm1/Algorithm1.h"
#include "GraphAlgorithms/TSPAlgorithms/Algorithm2/Algorithm2.h"
#include "GraphAlgorithms/TSPAlgorithms/ColonyAlgorithm/ColonyAlgorithm.h"

namespace s21 {

class GraphAlgorithms {
 public:
    /* Part 1*/
    [[nodiscard]] std::vector<int> DepthFirstSearch(const Graph &graph, int start_index);
    [[nodiscard]] std::vector<int> BreadthFirstSearch(const Graph &graph, int start_index);

    /* Part 2 */
    [[nodiscard]] int GetShortestPathBetweenVertices(const Graph &graph, int vertex_1, int vertex_2);
    [[nodiscard]] std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(const Graph&);

    /* Part 3 */
    [[nodiscard]] std::vector<std::vector<bool>> GetLeastSpanningTree(const Graph& graph);

    /* Part 4, 6 */
    [[nodiscard]] TspResult SolveTravelingSalesmanProblem(const Graph &graph, AlgorithmType algorithm_type);
 private:
    Graph graph_{};
    Algorithm1 algorithm_1_{};
    Algorithm2 algorithm_2_{};
    ColonyAlgorithm colony_algorithm_{};

};

}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_GRAPHALGORITHMS_H_
