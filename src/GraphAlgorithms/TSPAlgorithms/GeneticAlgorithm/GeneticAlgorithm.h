#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM2_ALGORITHM2_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM2_ALGORITHM2_H_

#include "Graph/Graph.h"
#include "common/structs.h"

namespace s21 {
class GeneticAlgorithm {
 public:
    [[nodiscard]] TspResult SolveTravelingSalesmanProblem(const Graph &graph);
 private:

};

}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM2_ALGORITHM2_H_
