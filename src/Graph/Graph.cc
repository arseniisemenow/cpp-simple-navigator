#include "Graph.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
void Graph::LoadGraphFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Read the number of vertices from the first line
    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "Failed to read number of vertices." << std::endl;
        return;
    }

    int num_vertices;
    try {
        num_vertices = std::stoi(line);
    } catch (const std::invalid_argument &e) {
        std::cerr << "Invalid number of vertices." << std::endl;
        return;
    }

    // Initialize the adjacency matrix with the correct size
    adjacency_matrix_.resize(num_vertices, std::vector<int>(num_vertices, 0));

    // Read the adjacency matrix
    for (int i = 0; i < num_vertices; ++i) {
        if (!std::getline(file, line)) {
            std::cerr << "Failed to read adjacency matrix." << std::endl;
            return;
        }

        std::istringstream iss(line);
        for (int j = 0; j < num_vertices; ++j) {
            int value;
            if (!(iss >> value)) {
                std::cerr << "Invalid value in adjacency matrix." << std::endl;
                return;
            }
            adjacency_matrix_[i][j] = value;
        }
    }
}
void Graph::ExportGraphToDot(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Write the header
    file << "graph G {\n";

    // Write the edges based on the adjacency matrix
    for (size_t i = 0; i < adjacency_matrix_.size(); ++i) {
        for (size_t j = i; j < adjacency_matrix_[i].size(); ++j) {
            if (adjacency_matrix_[i][j] != 0) {
                file << i << " -- " << j << " [label=\"" << adjacency_matrix_[i][j] << "\"];\n";
            }
        }
    }

    // Write the footer
    file << "}\n";
}

std::vector<std::vector<int>> Graph::GetGraph() {
    return adjacency_matrix_;
}
void Graph::SetGraph(const std::vector<std::vector<int>> &adjacency_matrix) {
    adjacency_matrix_ = adjacency_matrix;
}
}// namespace s21