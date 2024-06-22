#include <gtest/gtest.h>

#include "GraphAlgorithms/TSPAlgorithms/GeneticAlgorithm/GeneticAlgorithm.h"
#include "constants.h"

namespace s21 {
class GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest : public ::testing::Test {
 protected:
    void SetUp() override {}
    GeneticAlgorithm tsp_algorithm_{};
    Graph graph_{};
};

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest0) {
    graph_.LoadGraphFromFile(constants::kFileNames[0]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_TRUE(distance < 265);
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest1) {
    graph_.LoadGraphFromFile(constants::kFileNames[1]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, 0);
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest2) {
    graph_.LoadGraphFromFile(constants::kFileNames[2]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, 0);
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest3) {
    graph_.LoadGraphFromFile(constants::kFileNames[3]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, 0);
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest4) {
    graph_.LoadGraphFromFile(constants::kFileNames[4]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, 0);
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest5) {
    graph_.LoadGraphFromFile(constants::kFileNames[5]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, 0);
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest6) {
    graph_.LoadGraphFromFile(constants::kFileNames[6]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, 0);
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest7) {
    graph_.LoadGraphFromFile(constants::kFileNames[7]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_TRUE(distance < 10);
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest8) {
    graph_.LoadGraphFromFile(constants::kFileNames[8]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_TRUE(distance < 32);
}
}
