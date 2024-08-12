#include "ParseDatasetPath.h"

void ParseDatasetPath(const std::string& dataset_path,
                      std::vector<std::string>& graphs) {
  graphs.clear();
  for (const auto& entry : std::filesystem::directory_iterator(dataset_path)) {
    if (entry.is_regular_file() && entry.path().extension() == ".txt") {
      graphs.push_back(entry.path().string());
    }
  }
}
