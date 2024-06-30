#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_COMMON_STRUCTS_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_COMMON_STRUCTS_H_

#include <vector>

namespace s21 {
enum AlgorithmType {
  kNone = 0,
  kColonyAlgorithm = 1,
  kBrutForceAlgorithm = 2,
  kHeldKarpAlgorithm = 3,
  kGeneticAlgorithm = 4,
};

struct TspResult {
  std::vector<int> vertices;
  double distance;
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_COMMON_STRUCTS_H_
