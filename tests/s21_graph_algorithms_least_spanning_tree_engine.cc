#include <gtest/gtest.h>

#include "GraphAlgorithms/GraphAlgorithms.h"
#include "common/constants.h"
#include "constants.h"

namespace s21 {
class GraphAlgorithmsLeastSpanningTreeTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  GraphAlgorithms graph_algorithms_{};
  Graph graph_{};
};

TEST_F(GraphAlgorithmsLeastSpanningTreeTest, Test0) {
  graph_.LoadGraphFromFile(constants::kFileNames[8]);

  const auto least_spanning_tree =
      graph_algorithms_.GetLeastSpanningTree(graph_);
  const std::vector<std::vector<int>> expected_least_spanning_tree = {
      {0, 0, 0, 0, 5, 0}, {0, 0, 3, 0, 0, 0}, {0, 3, 0, 0, 0, 2},
      {0, 0, 0, 0, 0, 1}, {5, 0, 0, 0, 0, 4}, {0, 0, 2, 1, 4, 0}};
  ASSERT_EQ(least_spanning_tree, expected_least_spanning_tree);
}

TEST_F(GraphAlgorithmsLeastSpanningTreeTest, Test1) {
  graph_.LoadGraphFromFile(constants::kFileNames[0]);

  const auto least_spanning_tree =
      graph_algorithms_.GetLeastSpanningTree(graph_);
  const std::vector<std::vector<int>> expected_least_spanning_tree = {
      {0, 0, 0, 0, 0, 0, 0, 12, 4, 0, 0}, {0, 0, 0, 0, 0, 0, 72, 0, 0, 0, 12},
      {0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 13}, {0, 0, 0, 0, 4, 12, 0, 0, 0, 0, 0},
      {0, 0, 0, 4, 0, 0, 0, 9, 0, 0, 0},  {0, 0, 0, 12, 0, 0, 0, 0, 0, 3, 0},
      {0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {12, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0},
      {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  {0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
      {0, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0}};
  ASSERT_EQ(least_spanning_tree, expected_least_spanning_tree);
}
TEST_F(GraphAlgorithmsLeastSpanningTreeTest, Test2) {
  graph_.LoadGraphFromFile(constants::kFileNames[2]);

  const auto least_spanning_tree =
      graph_algorithms_.GetLeastSpanningTree(graph_);
  const std::vector<std::vector<int>> expected_least_spanning_tree = {
      {0, 1, 0, 1, 0, 0, 0, 0, 0, 0}, {1, 0, 1, 0, 1, 0, 1, 1, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 0, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0}};
  ASSERT_EQ(least_spanning_tree, expected_least_spanning_tree);
}

}  // namespace s21
