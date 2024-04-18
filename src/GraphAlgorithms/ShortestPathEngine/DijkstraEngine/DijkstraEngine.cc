#include "DijkstraEngine.h"

#include <limits>
#include <unordered_set>
#include <vector>

#include "common/constants.h"
#include "containers/adaptors/Queue/Queue.h"

namespace s21 {

int DijkstraEngine::GetCurrentMinimalIndex(const std::vector<int> distances, const std::unordered_set<int> visited) const {
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

void DijkstraEngine::UpdateDistances(const Graph& graph, const int current_vertex, const std::vector<int>& current_distances, std::vector<int>& updated_distances,
                     const std::unordered_set<int>& visited) {
    for (int i = 0; i < graph.GetSize(); ++i) {
        const int current_distance = graph.GetDistance(current_vertex, i);
        if (current_distance != constants::kInfinity && visited.find(i) == visited.end()) {
            if (updated_distances[i] > current_distances[current_vertex] + current_distance) {
                updated_distances[i] = current_distances[current_vertex] + graph.GetDistance(current_vertex, i);
            }
        }
    }
}

int DijkstraEngine::GetShortestPathBetweenVertices(const Graph& graph, int vertex_1, int vertex_2) {
    vertex_1 -= 1;
    vertex_2 -= 1;
    if (vertex_1 < 0 || vertex_2 < 0 || vertex_1 >= graph.GetGraph().size() || vertex_2 >= graph.GetSize()) {
        return 0;
    }

    std::vector<int> current_distances(graph.GetSize(), constants::kInfinity);
    std::vector<int> updated_distances(graph.GetSize());
    std::unordered_set<int> visited{};

    int current_vertex = vertex_1;

    current_distances[current_vertex] = 0;

    while (visited.size() < graph.GetSize() && current_vertex != -1) {

        visited.insert(current_vertex);
        updated_distances = current_distances;

        UpdateDistances(graph, current_vertex, current_distances, updated_distances, visited);
        current_vertex = GetCurrentMinimalIndex(updated_distances, visited);

        current_distances = updated_distances;
    }

    return updated_distances[vertex_2];
}
}// namespace s21
