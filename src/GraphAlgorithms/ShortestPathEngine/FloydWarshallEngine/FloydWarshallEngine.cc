#include "FloydWarshallEngine.h"

#include <regex>

namespace s21 {
void InitMatrix(const std::vector<std::vector<int>> &previous_adjacency_matrix, std::vector<std::vector<int>> &current_adjacency_matrix, const int pivot_index) {
    for (int i = 0; i < previous_adjacency_matrix.size(); ++i) {
        current_adjacency_matrix[pivot_index][i] = previous_adjacency_matrix[pivot_index][i];
    }
    for (int i = 0; i < previous_adjacency_matrix.size(); ++i) {
        current_adjacency_matrix[i][pivot_index] = previous_adjacency_matrix[i][pivot_index];
    }
    for (int i = 0; i < previous_adjacency_matrix.size(); ++i) {
        current_adjacency_matrix[i][i] = previous_adjacency_matrix[i][i];
    }
}

void FillMatrix(const std::vector<std::vector<int>> &previous_adjacency_matrix, std::vector<std::vector<int>> &current_adjacency_matrix, const int pivot_index) {
    for (int i = 0; i < previous_adjacency_matrix.size(); ++i) {
        if (i == pivot_index) {
            continue;
        }
        for (int j = 0; j < previous_adjacency_matrix.size(); ++j) {
            if (j == pivot_index || i == j) {
                continue;
            }
            const int distance = previous_adjacency_matrix[i][j];

            const int first_part_distance = previous_adjacency_matrix[i][pivot_index];
            const int second_part_distance = previous_adjacency_matrix[pivot_index][j];
            const int new_distance = first_part_distance + second_part_distance;

            if ((distance > 0 && distance > new_distance && first_part_distance > 0 && second_part_distance > 0) || (distance == 0 && first_part_distance > 0 && second_part_distance > 0)) {
                current_adjacency_matrix[i][j] = new_distance;
            } else {
                current_adjacency_matrix[i][j] = distance;
            }
        }
    }
}

std::vector<std::vector<int>> FloydWarshallEngine::GetShortestPathsBetweenAllVertices(const Graph &graph) {
    std::vector<std::vector<int>> previous_adjacency_matrix(graph.GetSize(), std::vector<int>(graph.GetSize()));
    std::vector<std::vector<int>> current_adjacency_matrix(graph.GetSize(), std::vector<int>(graph.GetSize()));

    previous_adjacency_matrix = graph.GetGraph();

    for (int i = 0; i < graph.GetSize(); ++i) {
        InitMatrix(previous_adjacency_matrix, current_adjacency_matrix, i);
        FillMatrix(previous_adjacency_matrix, current_adjacency_matrix, i);
        previous_adjacency_matrix = current_adjacency_matrix;
    }

    return previous_adjacency_matrix;
}
}// namespace s21
