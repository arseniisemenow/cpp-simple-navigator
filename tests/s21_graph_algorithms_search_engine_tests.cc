#include <gtest/gtest.h>

#include "GraphAlgorithms/GraphAlgorithms.h"
#include "constants.h"

namespace s21 {
class GraphAlgorithmsSearchEngineTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  GraphAlgorithms graph_algorithms_{};
  Graph graph_{};
};

TEST_F(GraphAlgorithmsSearchEngineTest, BreadthFirstSearchTest0) {
  graph_.LoadGraphFromFile(constants::kFileNames[0]);
  int start_index = 1;
  auto traverse_vector =
      graph_algorithms_.BreadthFirstSearch(graph_, start_index);
  std::vector<int> expected_traverse_vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  ASSERT_EQ(traverse_vector, expected_traverse_vector);
}
TEST_F(GraphAlgorithmsSearchEngineTest, BreadthFirstSearchTest1) {
  graph_.LoadGraphFromFile(constants::kFileNames[1]);
  int start_index = 1;
  auto traverse_vector =
      graph_algorithms_.BreadthFirstSearch(graph_, start_index);
  std::vector<int> expected_traverse_vector{1, 2, 3, 4};
  ASSERT_EQ(traverse_vector, expected_traverse_vector);
}
TEST_F(GraphAlgorithmsSearchEngineTest, BreadthFirstSearchTest2) {
  graph_.LoadGraphFromFile(constants::kFileNames[2]);
  int start_index = 1;
  auto traverse_vector =
      graph_algorithms_.BreadthFirstSearch(graph_, start_index);
  std::vector<int> expected_traverse_vector{1, 2, 4, 3, 5, 7, 8, 9, 10, 6};
  ASSERT_EQ(traverse_vector, expected_traverse_vector);
}
TEST_F(GraphAlgorithmsSearchEngineTest, BreadthFirstSearchTest3) {
  graph_.LoadGraphFromFile(constants::kFileNames[3]);
  int start_index = 1;
  auto traverse_vector =
      graph_algorithms_.BreadthFirstSearch(graph_, start_index);
  std::vector<int> expected_traverse_vector{1, 2, 3, 4, 5, 6, 7};
  ASSERT_EQ(traverse_vector, expected_traverse_vector);
}

TEST_F(GraphAlgorithmsSearchEngineTest, DepthFirstSearchTest0) {
  graph_.LoadGraphFromFile(constants::kFileNames[0]);
  int start_index = 1;
  auto traverse_vector =
      graph_algorithms_.DepthFirstSearch(graph_, start_index);
  std::vector<int> expected_traverse_vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  ASSERT_EQ(traverse_vector, expected_traverse_vector);
}
TEST_F(GraphAlgorithmsSearchEngineTest, DepthFirstSearchTest1) {
  graph_.LoadGraphFromFile(constants::kFileNames[1]);
  int start_index = 1;
  auto traverse_vector =
      graph_algorithms_.DepthFirstSearch(graph_, start_index);
  std::vector<int> expected_traverse_vector{1, 2, 3, 4};
  ASSERT_EQ(traverse_vector, expected_traverse_vector);
}
TEST_F(GraphAlgorithmsSearchEngineTest, DepthFirstSearchTest2) {
  graph_.LoadGraphFromFile(constants::kFileNames[2]);
  int start_index = 1;
  auto traverse_vector =
      graph_algorithms_.DepthFirstSearch(graph_, start_index);
  std::vector<int> expected_traverse_vector{1, 2, 3, 4, 9, 10, 5, 6, 7, 8};
  ASSERT_EQ(traverse_vector, expected_traverse_vector);
}
TEST_F(GraphAlgorithmsSearchEngineTest, DepthFirstSearchTest3) {
  graph_.LoadGraphFromFile(constants::kFileNames[3]);
  int start_index = 1;
  auto traverse_vector =
      graph_algorithms_.DepthFirstSearch(graph_, start_index);
  std::vector<int> expected_traverse_vector{1, 2, 4, 5, 3, 6, 7};
  ASSERT_EQ(traverse_vector, expected_traverse_vector);
}

}  // namespace s21
