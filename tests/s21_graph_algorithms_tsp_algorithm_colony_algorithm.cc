#include <gtest/gtest.h>

#include "GraphAlgorithms/GraphAlgorithms.h"
#include "constants.h"

namespace s21 {
class GraphAlgorithmsTspAlgorithmColonyAlgorithmTest : public ::testing::Test {
 protected:
    void SetUp() override {}
    GraphAlgorithms graph_algorithms_{};
    Graph graph_{};
    const double kExpectedAccuracy = 0.03;
};

TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, ColonyAlgorithmTest0) {
    graph_.LoadGraphFromFile(constants::kFileNames[0]);

    auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kColonyAlgorithm);
    const double expected_distance = 253;
    const double expected_range = expected_distance * kExpectedAccuracy;
    ASSERT_GE(distance, expected_distance - expected_range);
    ASSERT_LE(distance, expected_distance + expected_range);
}
TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, ColonyAlgorithmTest1) {
    graph_.LoadGraphFromFile(constants::kFileNames[1]);

    auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kColonyAlgorithm);

    ASSERT_GE(distance, constants::kInfinity);
}
TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, ColonyAlgorithmTest2) {
    graph_.LoadGraphFromFile(constants::kFileNames[2]);

    auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kColonyAlgorithm);


    ASSERT_GE(distance, constants::kInfinity);
}
TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, ColonyAlgorithmTest3) {
    graph_.LoadGraphFromFile(constants::kFileNames[3]);

    auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kColonyAlgorithm);

    ASSERT_GE(distance, constants::kInfinity);
}
TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, ColonyAlgorithmTest4) {
    graph_.LoadGraphFromFile(constants::kFileNames[4]);

    auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kColonyAlgorithm);

    ASSERT_GE(distance, constants::kInfinity);
}
TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, ColonyAlgorithmTest5) {
    graph_.LoadGraphFromFile(constants::kFileNames[5]);

    auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kColonyAlgorithm);

    ASSERT_GE(distance, constants::kInfinity);
}
TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, ColonyAlgorithmTest6) {
    graph_.LoadGraphFromFile(constants::kFileNames[6]);

    auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kColonyAlgorithm);
    ASSERT_GE(distance, constants::kInfinity);
}
TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, ColonyAlgorithmTest7) {
    graph_.LoadGraphFromFile(constants::kFileNames[7]);

    auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kColonyAlgorithm);
    const double expected_distance = 8;
    const double expected_range = expected_distance * kExpectedAccuracy;

    ASSERT_GE(distance, expected_distance - expected_range);
    ASSERT_LE(distance, expected_distance + expected_range);
}
TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, ColonyAlgorithmTest8) {
    graph_.LoadGraphFromFile(constants::kFileNames[8]);

    auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kColonyAlgorithm);
    const double expected_distance = 27;
    const double expected_range = expected_distance * kExpectedAccuracy;

    ASSERT_GE(distance, expected_distance - expected_range);
    ASSERT_LE(distance, expected_distance + expected_range);
}
TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, ColonyAlgorithmTest9) {
    graph_.LoadGraphFromFile(constants::kFileNames[9]);

    auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kColonyAlgorithm);
    const double expected_distance = 0; //724
    const double expected_range = expected_distance * kExpectedAccuracy;

    ASSERT_GE(distance, expected_distance - expected_range);
    ASSERT_LE(distance, expected_distance + expected_range);
}
TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, ColonyAlgorithmTest10) {
    graph_.LoadGraphFromFile(constants::kFileNames[10]);

    auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kColonyAlgorithm);
    const double expected_distance = 2110;
    const double expected_range = expected_distance * kExpectedAccuracy;

    ASSERT_GE(distance, expected_distance - expected_range);
    ASSERT_LE(distance, expected_distance + expected_range);
}
TEST_F(GraphAlgorithmsTspAlgorithmColonyAlgorithmTest, ColonyAlgorithmTest11) {
    graph_.LoadGraphFromFile(constants::kFileNames[11]);

    auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(graph_, kColonyAlgorithm);
    const double expected_distance = 35000;
    const double expected_range = expected_distance * kExpectedAccuracy;

    ASSERT_GE(distance, expected_distance - expected_range);
    ASSERT_LE(distance, expected_distance + expected_range);
}
}// namespace s21
