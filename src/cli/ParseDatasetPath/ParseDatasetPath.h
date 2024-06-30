#ifndef PARSEDATASETPATH_H
#define PARSEDATASETPATH_H

#include <__filesystem/directory_iterator.h>

#include <string>

void ParseDatasetPath(const std::string& dataset_path,
                      std::vector<std::string>& graphs);

#endif  // PARSEDATASETPATH_H
