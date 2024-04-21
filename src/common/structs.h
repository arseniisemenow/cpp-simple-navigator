#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_COMMON_STRUCTS_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_COMMON_STRUCTS_H_

#include <vector>

namespace s21 {
enum class AlgorithmType {
    kColonyAlgorithm = 1 << 0,
    kHeldKarpAlgorithm = 1 << 1,
    kGeneticAlgorithm = 1 << 2,
};

struct TspResult {
    std::vector<int> vertices;
    double distance;
};

}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_COMMON_STRUCTS_H_
