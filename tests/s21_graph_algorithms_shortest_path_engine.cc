#include <gtest/gtest.h>

#include "GraphAlgorithms/GraphAlgorithms.h"
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
    int shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, 1, 10);
    std::cerr << "shortest_path: " << shortest_path << "\n";
}
TEST_F(GraphAlgorithmsShortestPathEngineTest, Test1) {
    graph_.LoadGraphFromFile(constants::kFileNames[4]);
    const int shortest_path = graph_algorithms_.GetShortestPathBetweenVertices(graph_, 1, 6);
    std::cerr << "shortest_path: " << shortest_path << "\n";
}
}// namespace s21
