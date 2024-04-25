
#include "BrutForceAlgorithm.h"
#include "common/constants.h"
#include <random>


namespace s21 {

TspResult BrutForceAlgorithm::SolveTravelingSalesmanProblem(const Graph& graph) {
    int num_vertices = graph.GetSize();

    std::vector<int> vertices(num_vertices - 1);
    for (int i = 1; i < num_vertices; ++i) {
        vertices[i - 1] = i;
    }

    double min_distance = constants::kInfinity;
    std::vector<int> min_path;

    do {
        double total_distance = 0.0;
        bool valid_path = true;

        int current_vertex = 0; // Start at vertex 0
        for (int i = 0; i < num_vertices - 1; ++i) {
            int next_vertex = vertices[i];

            int distance = graph.GetDistance(current_vertex, next_vertex);
            if (distance == constants::kInfinity) {
                valid_path = false;
                break;
            }

            total_distance += distance;
            current_vertex = next_vertex;
        }

        int distance_to_start = graph.GetDistance(current_vertex, 0);
        if (distance_to_start == constants::kInfinity) {
            valid_path = false;
        } else {
            total_distance += distance_to_start;
        }

        if (valid_path && total_distance < min_distance) {
            min_distance = total_distance;
            min_path = vertices;
        }
    } while (std::next_permutation(vertices.begin(), vertices.end()));

    min_path.insert(min_path.begin(), 0);
    min_path.push_back(0);

    return {min_path, min_distance};
}

}// namespace s21