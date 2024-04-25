#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_COMMON_STRUCTS_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_COMMON_STRUCTS_H_

#include <vector>

namespace s21 {
enum AlgorithmType {
    kColonyAlgorithm = 1 << 0,
    kBrutForceAlgorithm = 1 << 1,
    kHeldKarpAlgorithm = 1 << 2,
    kGeneticAlgorithm = 1 << 3,
};


struct TspResult {
    std::vector<int> vertices;
    double distance;
};

}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_COMMON_STRUCTS_H_
