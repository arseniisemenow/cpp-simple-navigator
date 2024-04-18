#include <gtest/gtest.h>

#include "GraphAlgorithms/TSPAlgorithms/HeldKarpAlgorithm/HeldKarpAlgorithm.h"
#include "constants.h"

namespace s21 {
class GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest : public ::testing::Test {
 protected:
    void SetUp() override {}
    HeldKarpAlgorithm tsp_algorithm_{};
    Graph graph_{};
};

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, HeldKarpTest0) {
    graph_.LoadGraphFromFile(constants::kFileNames[0]);

    auto [vertices, distance] = tsp_algorithm_.SolveTravelingSalesmanProblem(graph_);

    std::cerr << "resulting distance: " << distance << '\n';
    std::cerr << "path: ";
    for (const auto& elem : vertices) {
        std::cerr << elem << ' ';
    }
    std::cerr << '\n';
}
}// namespace s21
