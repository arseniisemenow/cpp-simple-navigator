#include <gtest/gtest.h>

#include "GraphAlgorithms/GraphAlgorithms.h"
#include "common/constants.h"
#include "constants.h"

namespace s21 {
class GraphAlgorithmsShortestPathEngineTest : public ::testing::Test {
 protected:
    void SetUp() override {}
    GraphAlgorithms graph_algorithms_{};
    Graph graph_{};
};

TEST_F(GraphAlgorithmsShortestPathEngineTest, Test0) {
    graph_.LoadGraphFromFile(constants::kFileNames[0]);
    // int shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, 1, 10);
    // std::cerr << "shortest_path: " << shortest_path << "\n";
}
TEST_F(GraphAlgorithmsShortestPathEngineTest, Test1) {
    graph_.LoadGraphFromFile(constants::kFileNames[5]);
    int vertex_1 = 0;
    int vertex_2 = 0;
    int shortest_path = 0;

    vertex_1 = 1;
    vertex_2 = 6;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 9);

    vertex_1 = 1;
    vertex_2 = 5;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 6);

    vertex_1 = 1;
    vertex_2 = 4;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 8);

    vertex_1 = 1;
    vertex_2 = 3;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 3);

    vertex_1 = 1;
    vertex_2 = 2;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 2);

    vertex_1 = 1;
    vertex_2 = 1;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 0);
}
TEST_F(GraphAlgorithmsShortestPathEngineTest, Test2) {
    graph_.LoadGraphFromFile(constants::kFileNames[6]);
    int vertex_1 = 0;
    int vertex_2 = 0;
    int shortest_path = 0;

    vertex_1 = 1;
    vertex_2 = 6;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, constants::kInfinity);

    vertex_1 = 1;
    vertex_2 = 5;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 25);

    vertex_1 = 1;
    vertex_2 = 4;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 10);

    vertex_1 = 1;
    vertex_2 = 3;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 45);

    vertex_1 = 1;
    vertex_2 = 2;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 45);

    vertex_1 = 1;
    vertex_2 = 1;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 0);
}
TEST_F(GraphAlgorithmsShortestPathEngineTest, Test3) {
    graph_.LoadGraphFromFile(constants::kFileNames[6]);
    int vertex_1 = 0;
    int vertex_2 = 0;
    int shortest_path = 0;

    vertex_1 = 6;
    vertex_2 = 1;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 48);

    vertex_1 = 6;
    vertex_2 = 2;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 23);

    vertex_1 = 6;
    vertex_2 = 3;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 33);

    vertex_1 = 6;
    vertex_2 = 4;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 38);

    vertex_1 = 6;
    vertex_2 = 5;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 3);

    vertex_1 = 6;
    vertex_2 = 6;
    shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, vertex_1, vertex_2);
    ASSERT_EQ(shortest_path, 0);
}

TEST_F(GraphAlgorithmsShortestPathEngineTest, Test4) {
    graph_.LoadGraphFromFile(constants::kFileNames[7]);
    std::vector<std::vector<int>> shortest_paths{};
    const std::vector<std::vector<int>> expected_shortest_paths{
        {0, 3, 5, 6},
        {5, 0, 2, 3},
        {3, 6, 0, 1},
        {2, 5, 7, 0},
    };
    shortest_paths = graph_algorithms_.GetShortestPathsBetweenAllVertices(graph_);

    ASSERT_EQ(expected_shortest_paths, shortest_paths);
}
TEST_F(GraphAlgorithmsShortestPathEngineTest, Test5) {
    graph_.LoadGraphFromFile(constants::kFileNames[0]);
    std::vector<std::vector<int>> shortest_paths{};
    const std::vector<std::vector<int>> expected_shortest_paths{
        {0, 29, 20, 20, 16, 31, 100, 12, 4, 31, 18},
        {29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12},
        {20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13},
        {20, 29, 15, 0, 4, 12, 92, 12, 24, 13, 25},
        {16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22},
        {31, 40, 25, 12, 16, 0, 95, 24, 35, 3, 37},
        {100, 72, 81, 92, 94, 95, 0, 90, 101, 98, 84},
        {12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13},
        {4, 29, 23, 24, 20, 35, 101, 15, 0, 35, 18},
        {31, 41, 27, 13, 16, 3, 98, 25, 35, 0, 38},
        {18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0}};

    shortest_paths = graph_algorithms_.GetShortestPathsBetweenAllVertices(graph_);

    ASSERT_EQ(expected_shortest_paths, shortest_paths);
}
TEST_F(GraphAlgorithmsShortestPathEngineTest, Test6) {
    graph_.LoadGraphFromFile(constants::kFileNames[4]);
    std::vector<std::vector<int>> shortest_paths{};
    const std::vector<std::vector<int>> expected_shortest_paths{
        {0, 8, 4, 3, 7, 6},
        {8, 0, 4, 5, 7, 8},
        {4, 4, 0, 1, 3, 4},
        {3, 5, 1, 0, 4, 3},
        {7, 7, 3, 4, 0, 2},
        {6, 8, 4, 3, 2, 0}};

    shortest_paths = graph_algorithms_.GetShortestPathsBetweenAllVertices(graph_);

    ASSERT_EQ(expected_shortest_paths, shortest_paths);
}
TEST_F(GraphAlgorithmsShortestPathEngineTest, Test7) {
    graph_.LoadGraphFromFile(constants::kFileNames[6]);
    std::vector<std::vector<int>> shortest_paths{};
    const std::vector<std::vector<int>> expected_shortest_paths{
        {0, 45, 45, 10, 25, 0},
        {25, 0, 10, 15, 30, 0},
        {80, 55, 0, 70, 35, 0},
        {10, 35, 45, 0, 15, 0},
        {45, 20, 30, 35, 0, 0},
        {48, 23, 33, 38, 3, 0}};

    shortest_paths = graph_algorithms_.GetShortestPathsBetweenAllVertices(graph_);

    ASSERT_EQ(expected_shortest_paths, shortest_paths);
}
}// namespace s21
