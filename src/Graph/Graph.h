#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPH_GRAPH_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPH_GRAPH_H_

#include <iostream>
#include <vector>

namespace s21 {

class Graph {
 public:
    void LoadGraphFromFile(const std::string& filename);
    void ExportGraphToDot(const std::string& filename);
    [[nodiscard]] std::vector<std::vector<int>> GetGraph() const;
    void SetGraph(const std::vector<std::vector<int>>& adjacency_matrix);
 private:
    std::vector<std::vector<int>> adjacency_matrix_{};
};

}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPH_GRAPH_H_
