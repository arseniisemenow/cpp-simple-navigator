#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_GRAPHALGORITHMS_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_GRAPHALGORITHMS_H_

#include <array>

#include "Graph/Graph.h"
#include "GraphAlgorithms/SearchEngine/SearchEngine.h"
#include "GraphAlgorithms/ShortestPathEngine/ShortestPathEngine.h"
#include "GraphAlgorithms/LeastSpanningTreeEngine/LeastSpanningTreeEngine.h"
#include "GraphAlgorithms/TSPAlgorithms/ColonyAlgorithm/ColonyAlgorithm.h"
#include "GraphAlgorithms/TSPAlgorithms/BrutForceAlgorithm/BrutForceAlgorithm.h"
#include "GraphAlgorithms/TSPAlgorithms/GeneticAlgorithm/GeneticAlgorithm.h"
#include "GraphAlgorithms/TSPAlgorithms/HeldKarpAlgorithm/HeldKarpAlgorithm.h"
#include "common/structs.h"

namespace s21 {

class GraphAlgorithms {
 public:
    /* Part 1*/
    [[nodiscard]] std::vector<int> DepthFirstSearch(const Graph &graph, int start_index);
    [[nodiscard]] std::vector<int> BreadthFirstSearch(const Graph &graph, int start_index);

    /* Part 2 */
    /* Dijkstra's algorithm */
    [[nodiscard]] int GetShortestPathBetweenVertices(const Graph &graph, int vertex_1, int vertex_2);
    /* Floyd-Warshall algorithm */
    [[nodiscard]] std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(const Graph &);

    /* Part 3 */
    /* Prim's algorithm */
    [[nodiscard]] std::vector<std::vector<int>> GetLeastSpanningTree(const Graph &graph);

    /* Part 4, 6 */
    [[nodiscard]] TspResult SolveTravelingSalesmanProblem(const Graph &graph, AlgorithmType algorithm_type);

 private:
    Graph graph_{};
    SearchEngine search_engine_{};
    ShortestPathEngine shortest_path_engine_{};
    LeastSpanningTreeEngine least_spanning_tree_engine_{};
    ColonyAlgorithm colony_algorithm_{};
    BrutForceAlgorithm brut_force_algorithm_{};
    HeldKarpAlgorithm held_karp_algorithm_{};
    GeneticAlgorithm genetic_algorithm_{};
};

}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_GRAPHALGORITHMS_H_
