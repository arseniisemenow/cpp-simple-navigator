#include "GeneticAlgorithm.h"

#include <algorithm>
#include <random>
#include <unordered_set>

namespace s21::tsp_genetic_constants {
    inline constexpr int kPopulationSize{ 250 };
    inline constexpr double kCrossoverRate{ 0.8 };
    inline constexpr double kMutationRate{ 0.2 };
    inline constexpr int kNumberOfGenerations{ 200 };
}

namespace s21 {
TspResult GeneticAlgorithm::SolveTravelingSalesmanProblem(const Graph &graph) {
    TspResult result{};

    std::vector<std::vector<int>> population{ PerformGeneticAlgorithm(graph) };
    std::vector<int> total_distances_traveled{};
    for (const auto& individual : population) {
        total_distances_traveled.push_back(CalcualateDistanceTraveled(individual));
    }

    result.distance = *std::min_element(total_distances_traveled.begin(), total_distances_traveled.end());

    return result;
}

std::vector<std::vector<int>> GeneticAlgorithm::PerformGeneticAlgorithm(const Graph& graph) {
    distances_.clear();
    distances_ = graph.GetGraph();

    std::vector<int> list_of_cities{ graph.GetGraph()[0] };
    std::vector<std::vector<int>> population{ InitializePopulation(list_of_cities) };
    std::vector<double> fitness_probabilities{ CalculateFitnessProbabilities(population) };

    std::uniform_real_distribution<double> mutation_distr{ 0.0, 1.0 };
    for (int generation{ 0 };
        generation < tsp_genetic_constants::kNumberOfGenerations;
        ++generation) {
        std::vector<std::vector<int>> parents{};
        for (int i{ 0 };
             i < static_cast<int>(tsp_genetic_constants::kCrossoverRate *
                                  tsp_genetic_constants::kPopulationSize); ++i) {
            parents.push_back(SelectIndividual(population, fitness_probabilities));
        }

        // this loop is erroneous
        std::vector<std::vector<int>> offsprings{};
        for (std::size_t i{ 0 }; i < parents.size(); i += 2) {
            auto [first_offspring, second_offspring]{
                    CrossOver(parents[i], parents[i + 1]) };

            std::cerr << "i: " << i << '\n';
            double mutation_threshold{ mutation_distr(number_generator_) };
            if (mutation_threshold > (1.0 - tsp_genetic_constants::kMutationRate)) {
                first_offspring = MutateOffspring(first_offspring);
            }

            mutation_threshold = mutation_distr(number_generator_);
            if (mutation_threshold > (1.0 - tsp_genetic_constants::kMutationRate)) {
                second_offspring = MutateOffspring(second_offspring);
            }

            offsprings.push_back(first_offspring);
            offsprings.push_back(second_offspring);
        }

        std::vector<std::vector<int>> mixed_offsprings{ parents };
        mixed_offsprings.insert(mixed_offsprings.end(), offsprings.begin(), offsprings.end());

        fitness_probabilities = CalculateFitnessProbabilities(mixed_offsprings);
        std::vector<int> sorted_fitness_indices(fitness_probabilities.size());
        std::iota(sorted_fitness_indices.begin(), sorted_fitness_indices.end(), 0);
        std::sort(sorted_fitness_indices.begin(), sorted_fitness_indices.end(),
                [&](int i, int j) { return fitness_probabilities[i] > fitness_probabilities[j]; });

        std::vector<std::vector<int>> best_mixed_offsprings{};
        int number_of_best_offsprings{ static_cast<int>(0.8 * tsp_genetic_constants::kPopulationSize) };
        for (int i{ 0 }; i < number_of_best_offsprings; ++i) {
            best_mixed_offsprings.push_back(mixed_offsprings[sorted_fitness_indices[i]]);
        }

        std::vector<int> old_population_indices{};
        int old_population_size{ static_cast<int>(0.2 * tsp_genetic_constants::kPopulationSize) };
        std::uniform_int_distribution<int> distr{ 0, tsp_genetic_constants::kPopulationSize - 1 };
        for (int i{ 0 }; i < old_population_size; ++i) {
            old_population_indices.push_back(distr(number_generator_));
        }

        for (int i : old_population_indices) {
            best_mixed_offsprings.push_back(population[i]);
        }

        std::shuffle(best_mixed_offsprings.begin(), best_mixed_offsprings.end(), number_generator_);

        population = best_mixed_offsprings;
    }

    return population;
}

std::vector<std::vector<int>> GeneticAlgorithm::InitializePopulation(const std::vector<int>& list_of_cities) {
    std::vector<std::vector<int>> population{};
    std::vector<std::vector<int>> all_permutations{ GenerateAllPermutations(list_of_cities) };

    std::vector<int> random_identifiers(all_permutations.size());
    std::iota(random_identifiers.begin(), random_identifiers.end(), 0);
    std::shuffle(random_identifiers.begin(), random_identifiers.end(), number_generator_);
    random_identifiers.resize(tsp_genetic_constants::kPopulationSize);

    for (int i : random_identifiers) {
        population.push_back(all_permutations[i]);
    }

    return population;
}

struct VectorHash {
    size_t operator()(const std::vector<int>& vec) const {
        size_t hash = 0;
        for (int elem : vec) {
            hash ^= std::hash<int>()(elem) + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

std::vector<std::vector<int>> GeneticAlgorithm::GenerateAllPermutations(std::vector<int> list_of_cities) {
    std::vector<std::vector<int>> population_perms;
    std::unordered_set<std::vector<int>, VectorHash> unique_perms;

    std::random_device rd;
    std::mt19937 gen(rd());

    while (population_perms.size() < tsp_genetic_constants::kPopulationSize) {
        std::vector<int> perm = list_of_cities;
        std::shuffle(perm.begin(), perm.end(), gen);
        if (unique_perms.insert(perm).second) {
            population_perms.push_back(perm);
        }
    }

    return population_perms;
}

int GeneticAlgorithm::CalcualateDistanceTraveled(const std::vector<int>& cities) {
    int distance_traveled{ 0 };

    for (std::size_t i{ 0 }; i < cities.size(); ++i) {
        if (i == cities.size() - 1) {
            distance_traveled += distances_[i][0];
        } else {
            distance_traveled += distances_[i][i + 1];
        }
    }

    return distance_traveled;
}

std::vector<double> GeneticAlgorithm::CalculateFitnessProbabilities(
            const std::vector<std::vector<int>>& population) {
    std::vector<int> population_distances{};
    for (const auto& individual : population) {
        population_distances.push_back(CalcualateDistanceTraveled(individual));
    }

    int max_population_cost{ *std::max_element(population_distances.begin(), population_distances.end()) };
    std::vector<int> population_fitness{};
    for (int distance : population_distances) {
        population_fitness.push_back(max_population_cost - distance);
    }

    double population_fitness_sum{ static_cast<double>(std::reduce(population_fitness.begin(), population_fitness.end())) };

    std::vector<double> fitness_probabilities{};
    for (int fitness : population_fitness) {
        fitness_probabilities.push_back(fitness / population_fitness_sum);
    }

    return fitness_probabilities;
}

std::vector<int> GeneticAlgorithm::SelectIndividual(
        const std::vector<std::vector<int>>& population,
        const std::vector<double>& fitness_probabilities) {
    std::vector<double> fitness_probabilities_cumulative_sum(fitness_probabilities.size());
    std::partial_sum(fitness_probabilities.begin(), fitness_probabilities.end(), fitness_probabilities_cumulative_sum.begin());

    std::uniform_real_distribution<double> distribution{ 0.0, 1.0 };

    double random_number{ distribution(number_generator_) };
    // this doesnt work properly
    auto iter{ std::lower_bound(fitness_probabilities_cumulative_sum.begin(),
            fitness_probabilities_cumulative_sum.end(), random_number) };
    long selected_individual_index{
        std::distance(fitness_probabilities_cumulative_sum.begin(), iter) };

    return population[selected_individual_index];
}

std::pair<std::vector<int>, std::vector<int>> GeneticAlgorithm::CrossOver(
        const std::vector<int>& first_parent, const std::vector<int>& second_parent) {
    std::uniform_int_distribution<int> distribution{ 1, static_cast<int>(distances_.size() - 1) };
    int point_of_split{ distribution(number_generator_) };

    std::vector<int> first_offspring(first_parent.begin(), first_parent.begin() + point_of_split);
    std::vector<int> second_offspring(second_parent.begin(), second_parent.begin() + point_of_split);

    for (int i{ point_of_split }; i < static_cast<int>(first_parent.size()); ++i) {
        first_offspring[i] = second_parent[i];
        second_offspring[i] = first_parent[i];
    }

    return { first_offspring, second_offspring };
}

std::vector<int> GeneticAlgorithm::MutateOffspring(const std::vector<int>& offspring) {
    std::vector<int> mutated_offspring{ offspring };

    std::uniform_int_distribution<int> distribution{ 0, static_cast<int>(distances_.size() - 1) };

    std::pair<int, int> indices_to_swap{ distribution(number_generator_), distribution(number_generator_) };

    std::swap(mutated_offspring[indices_to_swap.first], mutated_offspring[indices_to_swap.second]);

    return mutated_offspring;
}
}// namespace s21
