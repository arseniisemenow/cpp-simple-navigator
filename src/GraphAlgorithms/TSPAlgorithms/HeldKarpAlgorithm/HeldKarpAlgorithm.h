#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM1_ALGORITHM1_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM1_ALGORITHM1_H_

#include "Graph/Graph.h"
#include "common/structs.h"

#include <set>
#include <vector>

namespace s21 {
class HeldKarpAlgorithm {
public:
    [[nodiscard]] TspResult SolveTravelingSalesmanProblem(const Graph &graph);

private:
    TspResult PerformHeldKarpAlgorithm(const Graph& graph);
    std::vector<std::set<int>> GenerateSubSets(int number_of_vertices);
    void GenerateCombination(const std::vector<int>& numbers, int start,
            int position, std::vector<std::set<int>>& sub_sets,
            std::vector<int>& result);

private:
};

}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM1_ALGORITHM1_H_
