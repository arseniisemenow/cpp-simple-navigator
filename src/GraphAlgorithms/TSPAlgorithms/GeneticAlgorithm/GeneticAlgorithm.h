#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM2_ALGORITHM2_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM2_ALGORITHM2_H_

#include "Graph/Graph.h"
#include "common/structs.h"

#include <random>
#include <vector>

namespace s21 {
class GeneticAlgorithm {
public:
    [[nodiscard]] TspResult SolveTravelingSalesmanProblem(const Graph &graph);
private:
    std::vector<std::vector<int>> PerformGeneticAlgorithm(const Graph& graph);

    std::vector<std::vector<int>> InitializePopulation(const std::vector<int>& list_of_cities);
    std::vector<std::vector<int>> GenerateAllPermutations(std::vector<int> list_of_cities);
    int CalcualateDistanceTraveled(const std::vector<int>& cities);
    std::vector<double> CalculateFitnessProbabilities(const std::vector<std::vector<int>>& population);
    std::vector<int> SelectIndividual(const std::vector<std::vector<int>>& population, const std::vector<double>& fitness_probabilities);
    std::pair<std::vector<int>, std::vector<int>> CrossOver(
          const std::vector<int>& first_parent, const std::vector<int>& second_parent);
    std::vector<int> MutateOffspring(const std::vector<int>& offspring);

private:
    std::vector<std::vector<int>> distances_{};
    std::mt19937 number_generator_{ std::random_device{}() };
};
}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPHALGORITHMS_TSPALGORITHMS_ALGORITHM2_ALGORITHM2_H_
