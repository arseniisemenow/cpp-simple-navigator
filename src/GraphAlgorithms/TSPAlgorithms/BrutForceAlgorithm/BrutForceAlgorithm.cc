
#include "BrutForceAlgorithm.h"
#include "common/constants.h"
#include <random>


namespace s21 {
TspResult BrutForceAlgorithm::SolveTravelingSalesmanProblem(const Graph& graph) {
  int num_vertices = graph.GetSize();
  std::vector<int> vertices(num_vertices);
  for (int i = 0; i < num_vertices; ++i) {
    vertices[i] = i;
  }

  double min_distance = std::numeric_limits<double>::infinity();
  std::vector<int> min_path;

  do {
    double current_distance = 0;
    bool valid_path = true;

    for (int i = 0; i < num_vertices - 1; ++i) {
      int distance = graph.GetDistance(vertices[i], vertices[i + 1]);
      if (distance == constants::kInfinity) {
        valid_path = false;
        break;
      }
      current_distance += distance;
    }

    if (valid_path) {
      int distance = graph.GetDistance(vertices[num_vertices - 1], vertices[0]);
      if (distance == constants::kInfinity) {
        valid_path = false;
      } else {
        current_distance += distance;
      }
    }

    if (valid_path && current_distance < min_distance) {
      min_distance = current_distance;
      min_path = vertices;
    }

  } while (std::next_permutation(vertices.begin() + 1, vertices.end()));

  return {min_path, min_distance};
}
}// namespace s21