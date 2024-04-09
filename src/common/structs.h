#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_COMMON_STRUCTS_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_COMMON_STRUCTS_H_

#include <vector>

namespace s21 {
typedef enum{
    kColonyAlgorithm = 0,
    kAlgorithm1,
    kAlgorithm2,
} AlgorithmType;

struct TspResult {
    std::vector<int> vertices;
    double distance;
};

}// namespace s21

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_COMMON_STRUCTS_H_
