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
    [[nodiscard]]int GetDistance(int vertex_1, int vertex_2) const;
    [[nodiscard]]int GetSize() const;
    void SetGraph(const std::vector<std::vector<int>>& adjacency_matrix);
    void Clear();
    bool IsEmpty() const;
 private:
    std::vector<std::vector<int>> adjacency_matrix_{};
};

}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPH_GRAPH_H_
