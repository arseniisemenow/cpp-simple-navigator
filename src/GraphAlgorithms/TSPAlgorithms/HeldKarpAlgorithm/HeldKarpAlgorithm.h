#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM1_ALGORITHM1_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM1_ALGORITHM1_H_

#include "Graph/Graph.h"
#include "common/structs.h"

#include <set>
#include <unordered_map>
#include <vector>

namespace s21 {
class HeldKarpAlgorithm {
public:
    [[nodiscard]] TspResult SolveTravelingSalesmanProblem(const Graph &graph);

private:
    TspResult PerformHeldKarpAlgorithm(const Graph& graph);
    void GenerateSubSets(int number_of_vertices);
    void GenerateCombination(const std::vector<int>& numbers,
                             std::size_t start, std::size_t position,
                             std::vector<int>& result);

    void IterateThroughSubSets(const std::vector<std::vector<int>>& distances,
                               int number_of_vertices);
    int GetCostSoFar(const std::set<int>& current_set, int previous_vertex);
    std::vector<int> GetPath();

private:
    // should probably move this elsewhere
struct Index {
    int current_vertex{};
    std::set<int> vertex_set{};

    bool operator==(const Index& other) const {
        return (current_vertex == other.current_vertex &&
                vertex_set == other.vertex_set);
    }
};

struct IndexHash {
    std::size_t operator()(const Index& index) const {
        std::size_t hash = std::hash<int>()(index.current_vertex);
        for (int vertex : index.vertex_set) {
            hash ^= std::hash<int>()(vertex);
        }
        return hash;
    }
};

private:
    std::vector<std::set<int>> sub_sets_{};
    std::unordered_map<Index, int, IndexHash> min_cost_map_{};
    std::unordered_map<Index, int, IndexHash> parent_{};
    std::vector<int> path_{};
};
}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM1_ALGORITHM1_H_
