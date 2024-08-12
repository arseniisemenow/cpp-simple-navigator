#include "GeneticAlgorithm.h"

#include <algorithm>
#include <random>
#include <unordered_set>

namespace s21::tsp_genetic_constants {
inline constexpr int kPopulationSize{250};
inline constexpr double kCrossoverRate{0.8};
inline constexpr double kMutationRate{0.2};
inline constexpr int kNumberOfGenerations{200};
}  // namespace s21::tsp_genetic_constants

namespace s21 {
TspResult GeneticAlgorithm::SolveTravelingSalesmanProblem(const Graph& graph) {
  if (graph.IsEmpty()) return {};
  TspResult result{};

  distances_.clear();
  distances_ = graph.GetGraph();

  std::vector<std::vector<int>> population{PerformGeneticAlgorithm(graph)};
  std::vector<int> total_distances_traveled{};
  total_distances_traveled.reserve(population.size());
  for (const auto& individual : population) {
    total_distances_traveled.push_back(
        CalcualateIndividualTotalDistance(individual));
  }

  int distance{*std::min_element(total_distances_traveled.begin(),
                                 total_distances_traveled.end())};
  if (distance == std::numeric_limits<int>::max()) {
    result.distance = std::numeric_limits<int>::max();
    result.vertices = {};
  } else {
    result.distance = distance;
    population.front().push_back(population.front()[0]);
    result.vertices = population.front();
  }

  return result;
}

std::vector<std::vector<int>> GeneticAlgorithm::PerformGeneticAlgorithm(
    const Graph& graph) {
  std::vector<int> list_of_cities{graph.GetGraph()[0]};
  std::vector<std::vector<int>> population{
      InitializePopulation(static_cast<int>(list_of_cities.size()))};

  for (int generation{0};
       generation < tsp_genetic_constants::kNumberOfGenerations; ++generation) {
    std::vector<double> fitness_probs{
        CalculateFitnessProbabilities(population)};
    std::vector<std::vector<int>> parents_list{};

    for (int i{0}; i < static_cast<int>(tsp_genetic_constants::kCrossoverRate *
                                        tsp_genetic_constants::kPopulationSize);
         ++i) {
      parents_list.push_back(SelectIndividual(population, fitness_probs));
    }

    std::vector<std::vector<int>> offspring_list{
        PerformMutations(parents_list)};

    std::vector<std::vector<int>> mixed_offspring{parents_list};
    mixed_offspring.insert(mixed_offspring.end(), offspring_list.begin(),
                           offspring_list.end());

    fitness_probs = CalculateFitnessProbabilities(mixed_offspring);
    std::vector<std::size_t> sorted_indices(mixed_offspring.size());
    std::iota(sorted_indices.begin(), sorted_indices.end(), 0);
    std::sort(sorted_indices.begin(), sorted_indices.end(),
              [&](std::size_t i, std::size_t j) {
                return fitness_probs[i] > fitness_probs[j];
              });

    std::vector<std::vector<int>> new_population{};
    for (std::size_t i{0}; i < tsp_genetic_constants::kPopulationSize; ++i) {
      new_population.push_back(mixed_offspring[sorted_indices[i]]);
    }

    population = new_population;
  }

  return population;
}

std::vector<std::vector<int>> GeneticAlgorithm::PerformMutations(
    const std::vector<std::vector<int>>& parents_list) {
  std::vector<std::vector<int>> offspring_list{};
  std::uniform_real_distribution<double> dist_mutation{0.0, 1.0};
  for (std::size_t i{0}; i < parents_list.size(); i += 2) {
    auto [offspring_1,
          offspring_2]{CrossOver(parents_list[i], parents_list[i + 1])};

    if (dist_mutation(number_generator_) <
        tsp_genetic_constants::kMutationRate) {
      offspring_1 = MutateOffspring(offspring_1);
    }
    if (dist_mutation(number_generator_) <
        tsp_genetic_constants::kMutationRate) {
      offspring_2 = MutateOffspring(offspring_2);
    }

    offspring_list.push_back(offspring_1);
    offspring_list.push_back(offspring_2);
  }

  return offspring_list;
}

std::vector<std::vector<int>> GeneticAlgorithm::InitializePopulation(
    int number_of_cities) {
  std::vector<std::vector<int>> population{};
  for (int i{0}; i < tsp_genetic_constants::kPopulationSize; ++i) {
    population.push_back(GeneratePermutation(number_of_cities));
  }

  return population;
}

std::vector<int> GeneticAlgorithm::GeneratePermutation(int size) {
  std::vector<int> permutation(size);
  std::iota(permutation.begin(), permutation.end(), 0);
  std::shuffle(permutation.begin(), permutation.end(), number_generator_);

  return permutation;
}

int GeneticAlgorithm::CalcualateIndividualTotalDistance(
    const std::vector<int>& individual) {
  int total_distance{0};
  const std::size_t number_of_cities{individual.size()};

  for (std::size_t i{0}; i < number_of_cities; ++i) {
    const int from{individual[i]};
    const int to{individual[(i + 1) % number_of_cities]};

    if (distances_[from][to] == 0) {
      return std::numeric_limits<int>::max();
    }

    total_distance += distances_[from][to];
  }
  return total_distance;
}

std::vector<double> GeneticAlgorithm::CalculateFitnessProbabilities(
    const std::vector<std::vector<int>>& population) {
  std::vector<int> total_dist_all_individuals(population.size());
  for (std::size_t i{0}; i < population.size(); ++i) {
    total_dist_all_individuals[i] =
        CalcualateIndividualTotalDistance(population[i]);
  }

  const int max_population_cost{*std::max_element(
      total_dist_all_individuals.begin(), total_dist_all_individuals.end())};
  std::vector<double> population_fitness(population.size());
  for (std::size_t i{0}; i < population.size(); ++i) {
    population_fitness[i] = max_population_cost - total_dist_all_individuals[i];
  }

  double population_fitness_sum{std::accumulate(population_fitness.begin(),
                                                population_fitness.end(), 0.0)};

  for (std::size_t i{0}; i < population_fitness.size(); ++i) {
    population_fitness[i] /= population_fitness_sum;
  }

  return population_fitness;
}

std::vector<int> GeneticAlgorithm::SelectIndividual(
    const std::vector<std::vector<int>>& population,
    const std::vector<double>& fitness_probabilities) {
  std::vector<double> fitness_probabilities_cumulative_sum(
      fitness_probabilities.size());
  std::partial_sum(fitness_probabilities.begin(), fitness_probabilities.end(),
                   fitness_probabilities_cumulative_sum.begin());

  std::uniform_real_distribution<double> distribution{0.0, 1.0};

  const double random_number{distribution(number_generator_)};
  const auto iter{std::lower_bound(fitness_probabilities_cumulative_sum.begin(),
                                   fitness_probabilities_cumulative_sum.end(),
                                   random_number)};
  const long selected_individual_index{
      std::distance(fitness_probabilities_cumulative_sum.begin(), iter)};

  return population[selected_individual_index];
}

std::pair<std::vector<int>, std::vector<int>> GeneticAlgorithm::CrossOver(
    const std::vector<int>& first_parent,
    const std::vector<int>& second_parent) {
  const int number_of_cities{static_cast<int>(first_parent.size())};

  std::uniform_int_distribution<int> dist_cut{1, number_of_cities - 1};
  const int cut{dist_cut(number_generator_)};

  std::vector<int> first_offspring{};
  std::vector<int> second_offspring{};

  first_offspring =
      std::vector<int>(first_parent.begin(), first_parent.begin() + cut);
  second_offspring =
      std::vector<int>(second_parent.begin(), second_parent.begin() + cut);

  for (int city : second_parent) {
    if (std::find(first_offspring.begin(), first_offspring.end(), city) ==
        first_offspring.end()) {
      first_offspring.push_back(city);
    }
  }

  for (int city : first_parent) {
    if (std::find(second_offspring.begin(), second_offspring.end(), city) ==
        second_offspring.end()) {
      second_offspring.push_back(city);
    }
  }

  return {first_offspring, second_offspring};
}

std::vector<int> GeneticAlgorithm::MutateOffspring(
    const std::vector<int>& offspring) {
  std::vector<int> mutated_offspring{offspring};
  const int number_of_cities{static_cast<int>(offspring.size())};
  std::uniform_int_distribution<int> dist_indices{0, number_of_cities - 1};
  const int index_1{dist_indices(number_generator_)};
  const int index_2{dist_indices(number_generator_)};

  std::swap(mutated_offspring[index_1], mutated_offspring[index_2]);

  return mutated_offspring;
}
}  // namespace s21
