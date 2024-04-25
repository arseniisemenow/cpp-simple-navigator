#include "ColonyAlgorithm.h"

#include <random>

namespace s21 {

constexpr double kAlpha = 1.0;           // Pheromone influence factor
constexpr double kBeta = 2.0;            // Distance influence factor
constexpr double kEvaporationRate = 0.1; // Pheromone evaporation rate
constexpr double kInitialPheromone = 1.0;// Initial pheromone level

TspResult ColonyAlgorithm::SolveTravelingSalesmanProblem(const Graph& graph) {
    int num_vertices = graph.GetSize();
    std::vector<std::vector<double>> pheromone(num_vertices, std::vector<double>(num_vertices, kInitialPheromone));
    TspResult best_solution;
    best_solution.distance = std::numeric_limits<double>::infinity();

    // Number of iterations and ants
    int num_iterations = 100;
    int num_ants = 10;

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // Perform iterations
    for (int iter = 0; iter < num_iterations; ++iter) {
        // Create solutions for each ant
        std::vector<TspResult> ant_solutions(num_ants);
        for (int ant = 0; ant < num_ants; ++ant) {
            TspResult solution;
            solution.vertices.push_back(0);// Start from vertex 0
            std::vector<bool> visited(num_vertices, false);
            visited[0] = true;

            // Construct solution
            for (int step = 0; step < num_vertices - 1; ++step) {
                int current_vertex = solution.vertices.back();
                double total_prob = 0.0;
                std::vector<double> probabilities(num_vertices, 0.0);

                // Calculate probabilities for selecting next vertex
                for (int next_vertex = 0; next_vertex < num_vertices; ++next_vertex) {
                    if (!visited[next_vertex]) {
                        double pheromone_level = std::pow(pheromone[current_vertex][next_vertex], kAlpha);
                        double distance = graph.GetDistance(current_vertex, next_vertex);
                        double attractiveness = 1.0 / distance;
                        probabilities[next_vertex] = pheromone_level * std::pow(attractiveness, kBeta);
                        total_prob += probabilities[next_vertex];
                    }
                }

                // Select next vertex based on probabilities
                double rand_val = dis(gen);
                double cumulative_prob = 0.0;
                for (int next_vertex = 0; next_vertex < num_vertices; ++next_vertex) {
                    if (!visited[next_vertex]) {
                        cumulative_prob += probabilities[next_vertex] / total_prob;
                        if (rand_val <= cumulative_prob) {
                            solution.vertices.push_back(next_vertex);
                            visited[next_vertex] = true;
                            break;
                        }
                    }
                }
            }

            // Add vertex 0 to complete the tour
            solution.vertices.push_back(0);

            // Calculate total distance of the solution
            solution.distance = 0.0;
            for (size_t i = 0; i < solution.vertices.size() - 1; ++i) {
                int vertex_1 = solution.vertices[i];
                int vertex_2 = solution.vertices[i + 1];
                solution.distance += graph.GetDistance(vertex_1, vertex_2);
            }

            // Update best solution if needed
            if (solution.distance < best_solution.distance) {
                best_solution = solution;
            }

            // Update pheromone levels on edges
            for (size_t i = 0; i < solution.vertices.size() - 1; ++i) {
                int vertex_1 = solution.vertices[i];
                int vertex_2 = solution.vertices[i + 1];
                pheromone[vertex_1][vertex_2] += 1.0 / solution.distance;// Deposit pheromone
                pheromone[vertex_2][vertex_1] += 1.0 / solution.distance;// Update pheromone on both directions
            }
        }

        // Evaporate pheromone
        for (int i = 0; i < num_vertices; ++i) {
            for (int j = 0; j < num_vertices; ++j) {
                pheromone[i][j] *= (1.0 - kEvaporationRate);
            }
        }
    }

    return best_solution;
}
}// namespace s21