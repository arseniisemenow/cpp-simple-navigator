#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM2_ALGORITHM2_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM2_ALGORITHM2_H_

#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "Graph/Graph.h"
#include "common/structs.h"

namespace s21 {
class GeneticAlgorithm {
 public:
  [[nodiscard]] TspResult SolveTravelingSalesmanProblem(const Graph& graph);

 private:
  std::vector<std::vector<int>> PerformGeneticAlgorithm(const Graph& graph);

  std::vector<std::vector<int>> PerformMutations(
      const std::vector<std::vector<int>>& parents_list);
  std::vector<std::vector<int>> InitializePopulation(int number_of_cities);
  std::vector<int> GeneratePermutation(int size);
  int CalcualateIndividualTotalDistance(const std::vector<int>& individual);
  std::vector<double> CalculateFitnessProbabilities(
      const std::vector<std::vector<int>>& population);
  std::vector<int> SelectIndividual(
      const std::vector<std::vector<int>>& population,
      const std::vector<double>& fitness_probabilities);
  std::pair<std::vector<int>, std::vector<int>> CrossOver(
      const std::vector<int>& first_parent,
      const std::vector<int>& second_parent);
  std::vector<int> MutateOffspring(const std::vector<int>& offspring);

 private:
  std::vector<std::vector<int>> distances_{};
  std::mt19937 number_generator_{std::random_device{}()};

  FRIEND_TEST(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest,
              GeneratePermutationTest);
  FRIEND_TEST(GraphAlgorithmsTspAlgorithmGeneticAlgorithmTest,
              CalcualateIndividualTotalDistanceTest);
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM2_ALGORITHM2_H_
