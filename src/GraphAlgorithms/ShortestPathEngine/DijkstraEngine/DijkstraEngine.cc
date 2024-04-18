#include "DijkstraEngine.h"

#include "containers/adaptors/Queue/Queue.h"

namespace s21 {

int DijkstraEngine::GetShortestPathBetweenVertices(const Graph &graph, int vertex_1, int vertex_2) {
    vertex_1 -= 1;
    vertex_2 -= 1;
    // Get the adjacency matrix of the graph
    std::vector<std::vector<int>> adjacency_matrix = graph.GetGraph();
    int num_vertices = adjacency_matrix.size();

    // Initialize distance array and visited array
    std::vector<int> distance(num_vertices, kInfinity);
    std::vector<bool> visited(num_vertices, false);

    // Custom queue to store vertices and their distances
    Queue<std::pair<int, int>> pq;

    // Start from vertex_1
    distance[vertex_1] = 0;
    pq.push({0, vertex_1});

    while (!pq.empty()) {
        int u = pq.front().second;
        pq.pop();

        if (u == vertex_2) {
            return distance[u];
        }

        // Mark vertex u as visited
        visited[u] = true;

        // Update distances of adjacent vertices of u
        for (int v = 0; v < num_vertices; ++v) {
            if (!visited[v] && adjacency_matrix[u][v] != 0 && distance[u] + adjacency_matrix[u][v] < distance[v]) {
                distance[v] = distance[u] + adjacency_matrix[u][v];
                pq.push({distance[v], v});
            }
        }
    }

    // If vertex_2 is not reachable from vertex_1
    return kInfinity;
}
}// namespace s21
