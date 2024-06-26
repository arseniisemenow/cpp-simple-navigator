#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_CLI_TSP_SINGLE_ALGORITHM_MODE_TSP_SINGLE_ALGORITHM_MODE_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_CLI_TSP_SINGLE_ALGORITHM_MODE_TSP_SINGLE_ALGORITHM_MODE_H_

#include <iostream>
#include <string>
#include <vector>

#include "common/structs.h"

void TSPComparisonMode(const std::vector<std::string> &graphs, int &selected_graph_index, std::vector<s21::AlgorithmType> &selected_algorithms, int &num_runs);

#endif//A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_CLI_TSP_SINGLE_ALGORITHM_MODE_TSP_SINGLE_ALGORITHM_MODE_H_