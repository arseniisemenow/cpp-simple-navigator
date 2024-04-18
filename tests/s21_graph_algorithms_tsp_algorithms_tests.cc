#include <gtest/gtest.h>

#include "GraphAlgorithms/TSPAlgorithms/HeldKarpAlgorithm/HeldKarpAlgorithm.h"
#include "constants.h"

namespace s21 {
class GraphAlgorithmsTspAlgorithmsTest : public ::testing::Test {
 protected:
    void SetUp() override {}
    HeldKarpAlgorithm tsp_algorithm_{};
    Graph graph_{};
};

TEST_F(GraphAlgorithmsTspAlgorithmsTest, HeldKarpTest0) {
    graph_.LoadGraphFromFile(constants::kFileNames[0]);

    auto result{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    std::cerr << "resulting distance: " << result.distance << '\n';
    std::cerr << "path: ";
    for (const auto& elem : result.vertices) {
       std::cerr << elem << ' ';
    }
    std::cerr << '\n';
}
}
