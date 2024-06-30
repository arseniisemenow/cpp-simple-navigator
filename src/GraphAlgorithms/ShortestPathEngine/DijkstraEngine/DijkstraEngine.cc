#include "DijkstraEngine.h"

#include <limits>
#include <unordered_set>
#include <vector>

#include "common/constants.h"

namespace s21 {

int DijkstraEngine::GetCurrentMinimalIndex(
    const std::vector<int>& distances,
    const std::unordered_set<int>& visited) const {
  int min_distance = constants::kInfinity;
  int min_index = -1;
  for (int i = 0; i < distances.size(); ++i) {
    if (visited.find(i) == visited.end() && distances[i] < min_distance) {
      min_distance = distances[i];
      min_index = i;
    }
  }
  return min_index;
}

void DijkstraEngine::UpdateDistances(
    const Graph& graph, const int current_vertex,
    std::vector<int>& updated_distances,
    const std::unordered_set<int>& visited) const {
  for (int i = 0; i < graph.GetSize(); ++i) {
    const int current_distance = graph.GetDistance(current_vertex, i);
    if (current_distance != constants::kInfinity &&
        visited.find(i) == visited.end()) {
      if (updated_distances[i] >
          updated_distances[current_vertex] + current_distance) {
        updated_distances[i] = updated_distances[current_vertex] +
                               graph.GetDistance(current_vertex, i);
      }
    }
  }
}

int DijkstraEngine::GetShortestPathBetweenVertices(const Graph& graph,
                                                   int vertex_1, int vertex_2) {
  vertex_1 -= 1;
  vertex_2 -= 1;
  if (graph.IsEmpty()) {
    return 0;
  }
  if (vertex_1 < 0 || vertex_2 < 0 || vertex_1 >= graph.GetGraph().size() ||
      vertex_2 >= graph.GetSize()) {
    return 0;
  }

  std::vector<int> distances(graph.GetSize(), constants::kInfinity);
  std::unordered_set<int> visited{};

  int current_vertex = vertex_1;

  distances[current_vertex] = 0;

  while (visited.size() < graph.GetSize() && current_vertex != -1) {
    visited.insert(current_vertex);
    UpdateDistances(graph, current_vertex, distances, visited);
    current_vertex = GetCurrentMinimalIndex(distances, visited);
  }

  return distances[vertex_2];
}
}  // namespace s21
