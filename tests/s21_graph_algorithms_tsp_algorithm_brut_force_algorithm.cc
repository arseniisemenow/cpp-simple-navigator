#include <gtest/gtest.h>

#include "GraphAlgorithms/GraphAlgorithms.h"
#include "constants.h"

namespace s21 {
class GraphAlgorithmsTspAlgorithmBrutForceAlgorithmTest : public ::testing::Test {
 protected:
    void SetUp() override {}
    GraphAlgorithms graph_algorithms_{};
    Graph graph_{};
};

TEST_F(GraphAlgorithmsTspAlgorithmBrutForceAlgorithmTest, BrutForceTest0) {
    graph_.LoadGraphFromFile(constants::kFileNames[0]);

    auto [vertices_1, distance_1] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kBrutForceAlgorithm);
    auto [vertices_2, distance_2] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kHeldKarpAlgorithm);

    std::cerr << "resulting distance: " << distance_1 << '\n';
    std::cerr << "path: ";
    for (const auto& elem : vertices_1) {
        std::cerr << elem << ' ';
    }
    std::cerr << '\n';
    std::cerr << "resulting distance: " << distance_2 << '\n';
    std::cerr << "path: ";
    for (const auto& elem : vertices_2) {
        std::cerr << elem << ' ';
    }
    std::cerr << '\n';
}
}// namespace s21
