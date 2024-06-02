#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_CLI_CHOOSEFILEPATH_CHOOSEFILEPATH_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_CLI_CHOOSEFILEPATH_CHOOSEFILEPATH_H_

#include <string>

std::vector<std::string> ListDirectories(const std::string &path);
void ChooseFilePath(std::string &dataset_path);
std::string GetCurrentWorkingDirectory();
std::string FindDatasetDirectory(const std::string &path, int depth = 5);

#endif //A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_CLI_CHOOSEFILEPATH_CHOOSEFILEPATH_H_
