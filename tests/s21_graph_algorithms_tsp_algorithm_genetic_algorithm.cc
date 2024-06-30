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

  auto [vertices,
        distance]{tsp_algorithm_.SolveTravelingSalesmanProblem(graph_)};

  ASSERT_TRUE(distance < 265);
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest1) {
  graph_.LoadGraphFromFile(constants::kFileNames[1]);

  auto [vertices,
        distance]{tsp_algorithm_.SolveTravelingSalesmanProblem(graph_)};

  ASSERT_EQ(distance, std::numeric_limits<int>::max());
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest2) {
  graph_.LoadGraphFromFile(constants::kFileNames[2]);

  auto [vertices,
        distance]{tsp_algorithm_.SolveTravelingSalesmanProblem(graph_)};

  ASSERT_EQ(distance, std::numeric_limits<int>::max());
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest3) {
  graph_.LoadGraphFromFile(constants::kFileNames[3]);

  auto [vertices,
        distance]{tsp_algorithm_.SolveTravelingSalesmanProblem(graph_)};

  ASSERT_EQ(distance, std::numeric_limits<int>::max());
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest4) {
  graph_.LoadGraphFromFile(constants::kFileNames[4]);

  auto [vertices,
        distance]{tsp_algorithm_.SolveTravelingSalesmanProblem(graph_)};

  ASSERT_EQ(distance, std::numeric_limits<int>::max());
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest5) {
  graph_.LoadGraphFromFile(constants::kFileNames[5]);

  auto [vertices,
        distance]{tsp_algorithm_.SolveTravelingSalesmanProblem(graph_)};

  ASSERT_EQ(distance, std::numeric_limits<int>::max());
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest6) {
  graph_.LoadGraphFromFile(constants::kFileNames[6]);

  auto [vertices,
        distance]{tsp_algorithm_.SolveTravelingSalesmanProblem(graph_)};

  ASSERT_EQ(distance, std::numeric_limits<int>::max());
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest7) {
  graph_.LoadGraphFromFile(constants::kFileNames[7]);

  auto [vertices,
        distance]{tsp_algorithm_.SolveTravelingSalesmanProblem(graph_)};

  ASSERT_TRUE(distance < 10);
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest, GeneticTest8) {
  graph_.LoadGraphFromFile(constants::kFileNames[8]);

  auto [vertices,
        distance]{tsp_algorithm_.SolveTravelingSalesmanProblem(graph_)};

  ASSERT_TRUE(distance < 32);
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest,
       GeneratePermutationTest) {
  std::vector<int> permutation{tsp_algorithm_.GeneratePermutation(10)};

  EXPECT_EQ(permutation.size(), 10);

  std::set<int> unique_elements(permutation.begin(), permutation.end());
  EXPECT_EQ(unique_elements.size(), permutation.size());

  std::vector<int> sorted_permutation = permutation;
  std::sort(sorted_permutation.begin(), sorted_permutation.end());
  EXPECT_NE(permutation, sorted_permutation);
}

TEST_F(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest,
       CalcualateIndividualTotalDistanceTest) {
  std::vector<int> permutation{0, 1, 2, 3};
  tsp_algorithm_.distances_ = {
      {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};

  int total_distance{
      tsp_algorithm_.CalcualateIndividualTotalDistance(permutation)};

  int expected_distance{10 + 35 + 30 + 20};
  EXPECT_EQ(total_distance, expected_distance);
}
}  // namespace s21
