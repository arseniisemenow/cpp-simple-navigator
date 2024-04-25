#include <gtest/gtest.h>

#include "GraphAlgorithms/GraphAlgorithms.h"
#include "GraphAlgorithms/TSPAlgorithms/HeldKarpAlgorithm/HeldKarpAlgorithm.h"
#include "constants.h"

namespace s21 {
class GraphAlgorithmsTspAlgorithmColonyAlgorithmTest : public ::testing::Test {
 protected:
    void SetUp() override {}
    GraphAlgorithms graph_algorithms_{};
    Graph graph_{};
};

TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, GraphAlgorithmsTspAlgorithmColonyAlgorithmTest0) {
    graph_.LoadGraphFromFile(constants::kFileNames[4]);
    const auto tsp_result = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, AlgorithmType::kColonyAlgorithm);
    const auto tsp_result_brut_force = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, AlgorithmType::kBrutForceAlgorithm);
//    std::cerr << "tsp_result number: " << tsp_result.distance << "\n";
    std::cerr << "tsp_result_brut_force number: " << tsp_result_brut_force.distance << "\n";
    std::cerr << "\n";
    for (auto item: tsp_result_brut_force.vertices) {
        std::cerr << " " << item + 1;
    }
}
}
