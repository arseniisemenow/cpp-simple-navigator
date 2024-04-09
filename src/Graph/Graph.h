#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPH_GRAPH_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPH_GRAPH_H_

#include <iostream>

namespace s21 {

class Graph {
 public:
    void LoadGraphFromFile(const std::string& filename);
    void ExportGraphToDot(const std::string& filename);
};

}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_GRAPH_GRAPH_H_
