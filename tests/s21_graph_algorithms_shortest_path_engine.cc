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
}// namespace s21
