#include "ColonyAlgorithm.h"

#include <random>

#include "common/constants.h"

namespace s21 {

constexpr int kStartingIndex = 0;
constexpr double kAlpha = 1.0;
constexpr double kBeta = 2.0;
constexpr double kEvaporationRate = 0.1;
constexpr double kInitialPheromone = 1.0;
constexpr int kIterationsCount = 250;
constexpr int kAntsCount = 50;

void InitializePheromoneLevels(std::vector<std::vector<double>>& pheromone) {
  const int num_vertices = static_cast<int>(pheromone.size());
  for (int i = 0; i < num_vertices; ++i) {
    for (int j = 0; j < num_vertices; ++j) {
      pheromone[i][j] = kInitialPheromone;
    }
  }
}

int GetNextCity(const int num_vertices, std::vector<bool> visited,
                const std::vector<double>& probabilities,
                const double total_prob) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0.0, 1.0);

  const double rand_val = dis(gen);
  double cumulative_probability = 0.0;
  for (int next_vertex = 0; next_vertex < num_vertices; ++next_vertex) {
    if (!visited[next_vertex]) {
      cumulative_probability += probabilities[next_vertex] / total_prob;
      if (rand_val <= cumulative_probability) {
        return next_vertex;
      }
    }
  }
  return kStartingIndex;
}

TspResult ConstructAntTour(const Graph& graph,
                           const std::vector<std::vector<double>>& pheromone) {
  const int num_vertices = graph.GetSize();
  TspResult solution{};
  solution.vertices.push_back(kStartingIndex);
  std::vector<bool> visited(num_vertices, false);
  visited[0] = true;

  for (int step = 0; step < num_vertices - 1; ++step) {
    const int current_vertex = solution.vertices.back();
    double total_prob = 0.0;
    std::vector<double> probabilities(num_vertices, 0.0);

    for (int next_vertex = 0; next_vertex < num_vertices; ++next_vertex) {
      if (!visited[next_vertex]) {
        const double pheromone_level =
            std::pow(pheromone[current_vertex][next_vertex], kAlpha);
        const double distance = graph.GetDistance(current_vertex, next_vertex);
        const double attractiveness = 1.0 / distance;
        probabilities[next_vertex] =
            pheromone_level * std::pow(attractiveness, kBeta);
        total_prob += probabilities[next_vertex];
      }
    }

    const int next_vertex =
        GetNextCity(num_vertices, visited, probabilities, total_prob);
    visited[next_vertex] = true;
    solution.vertices.push_back(next_vertex);
  }

  solution.vertices.push_back(kStartingIndex);

  solution.distance = 0.0;
  for (size_t i = 0; i < solution.vertices.size() - 1; ++i) {
    const int vertex_1 = solution.vertices[i];
    const int vertex_2 = solution.vertices[i + 1];
    solution.distance += graph.GetDistance(vertex_1, vertex_2);
  }

  return solution;
}

void UpdatePheromoneLevels(std::vector<std::vector<double>>& pheromone,
                           const std::vector<TspResult>& ant_solutions) {
  for (const auto& [vertices, distance] : ant_solutions) {
    for (size_t i = 0; i < vertices.size() - 1; ++i) {
      const int vertex_1 = vertices[i];
      const int vertex_2 = vertices[i + 1];
      pheromone[vertex_1][vertex_2] += 1.0 / distance;
      pheromone[vertex_2][vertex_1] += 1.0 / distance;
    }
  }
}

void EvaporatePheromone(std::vector<std::vector<double>>& pheromone) {
  const int num_vertices = static_cast<int>(pheromone.size());
  for (int i = 0; i < num_vertices; ++i) {
    for (int j = 0; j < num_vertices; ++j) {
      pheromone[i][j] *= (1.0 - kEvaporationRate);
    }
  }
}

TspResult ColonyAlgorithm::SolveTravelingSalesmanProblem(const Graph& graph) {
  const int num_vertices = graph.GetSize();
  std::vector<std::vector<double>> pheromone(num_vertices,
                                             std::vector<double>(num_vertices));
  InitializePheromoneLevels(pheromone);
  TspResult best_solution;
  best_solution.distance = constants::kInfinity;

  for (int iter = 0; iter < kIterationsCount; ++iter) {
    std::vector<TspResult> ant_solutions(kAntsCount);
    for (int ant_index = 0; ant_index < kAntsCount; ++ant_index) {
      ant_solutions[ant_index] = ConstructAntTour(graph, pheromone);
      if (ant_solutions[ant_index].distance < best_solution.distance) {
        best_solution = ant_solutions[ant_index];
      }
    }

    UpdatePheromoneLevels(pheromone, ant_solutions);

    EvaporatePheromone(pheromone);
  }

  return best_solution;
}
}  // namespace s21