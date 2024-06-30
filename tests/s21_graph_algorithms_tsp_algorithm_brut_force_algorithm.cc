#include <gtest/gtest.h>

#include "GraphAlgorithms/GraphAlgorithms.h"
#include "constants.h"

namespace s21 {
class GraphAlgorithmsTspAlgorithmBrutForceAlgorithmTest
    : public ::testing::Test {
 protected:
  void SetUp() override {}
  GraphAlgorithms graph_algorithms_{};
  Graph graph_{};
};

TEST_F(GraphAlgorithmsTspAlgorithmBrutForceAlgorithmTest, BrutForceTest0) {
  graph_.LoadGraphFromFile(constants::kFileNames[0]);

  auto [tour, distance] = graph_algorithms_.SolveTravelingSalesmanProblem(
      graph_, kBrutForceAlgorithm);
  const int expected_distance = 0;
  const std::vector<int> expected_tour{0, 7, 4, 3, 9, 5, 2, 6, 1, 10, 8, 0};
  ASSERT_EQ(tour, expected_tour);
  ASSERT_EQ(distance, 253);
}
}  // namespace s21
