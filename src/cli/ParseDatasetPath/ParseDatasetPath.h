#ifndef PARSEDATASETPATH_H
#define PARSEDATASETPATH_H

#include <filesystem>
#include <string>
#include <vector>

void ParseDatasetPath(const std::string& dataset_path,
                      std::vector<std::string>& graphs);

#endif  // PARSEDATASETPATH_H
