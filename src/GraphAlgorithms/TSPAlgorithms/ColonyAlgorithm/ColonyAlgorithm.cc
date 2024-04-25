#include "ColonyAlgorithm.h"

#include <random>

namespace s21 {

    // Helper function to initialize pheromone levels on edges
    void InitializePheromones(std::vector<std::vector<double>>& pheromone_matrix) {
        // Initialize pheromone levels to a small value
        const double initial_pheromone = 0.1;
        for (auto& row : pheromone_matrix) {
            for (auto& pheromone : row) {
                pheromone = initial_pheromone;
            }
        }
    }

    // Helper function to select the next city for an ant to visit
    int SelectNextCity(const Graph& graph, int current_city, const std::vector<bool>& visited,
                       const std::vector<std::vector<double>>& pheromone_matrix) {
        // Calculate probabilities for each city based on pheromone levels and heuristic information
        std::vector<double> probabilities(graph.GetSize(), 0.0);
        double total_prob = 0.0;
        for (int city = 0; city < graph.GetSize(); ++city) {
            if (!visited[city]) {
                double pheromone = pheromone_matrix[current_city][city];
                double heuristic = 1.0 / graph.GetDistance(current_city, city); // Inverse of distance as heuristic
                probabilities[city] = pheromone * heuristic;
                total_prob += probabilities[city];
            }
        }

        // Select a city probabilistically
        double rand_num = static_cast<double>(rand()) / RAND_MAX;
        double cumulative_prob = 0.0;
        for (int city = 0; city < graph.GetSize(); ++city) {
            if (!visited[city]) {
                cumulative_prob += probabilities[city] / total_prob;
                if (rand_num <= cumulative_prob) {
                    return city;
                }
            }
        }
        // Should not reach here under normal circumstances
        return -1;
    }

    TspResult ColonyAlgorithm::SolveTravelingSalesmanProblem(const Graph& graph) {
        // Initialize variables
        const int num_ants = 10;
        const int num_iterations = 100;
        std::vector<std::vector<double>> pheromone_matrix(graph.GetSize(), std::vector<double>(graph.GetSize(), 0.0));
        InitializePheromones(pheromone_matrix);

        TspResult best_solution;
        best_solution.distance = std::numeric_limits<double>::max();

        // Main loop
        for (int iter = 0; iter < num_iterations; ++iter) {
            // Construct solutions for each ant
            for (int ant = 0; ant < num_ants; ++ant) {
                std::vector<bool> visited(graph.GetSize(), false);
                std::vector<int> tour;
                tour.push_back(0); // Start from city 0
                visited[0] = true;
                double total_distance = 0.0;

                // Build the tour for the ant
                for (int step = 1; step < graph.GetSize(); ++step) {
                    int current_city = tour.back();
                    int next_city = SelectNextCity(graph, current_city, visited, pheromone_matrix);
                    tour.push_back(next_city);
                    visited[next_city] = true;
                    total_distance += graph.GetDistance(current_city, next_city);
                }
                // Return to the starting city
                total_distance += graph.GetDistance(tour.back(), 0);
                tour.push_back(0);
                // Update the best solution if needed
                if (total_distance < best_solution.distance) {
                    best_solution.vertices = tour;
                    best_solution.distance = total_distance;
                }
            }
            // Update pheromone levels based on the tours constructed by ants
            // (This part is not implemented in this breakdown)
        }

        return best_solution;
    }
}// namespace s21