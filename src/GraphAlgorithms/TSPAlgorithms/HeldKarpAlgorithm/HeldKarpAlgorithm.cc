#include "HeldKarpAlgorithm.h"

#include "common/structs.h"

#include <algorithm>
#include <numeric>

namespace s21 {
TspResult HeldKarpAlgorithm::SolveTravelingSalesmanProblem(const Graph &graph) {
    TspResult result{ PerformHeldKarpAlgorithm(graph) };
    return result;
}

TspResult HeldKarpAlgorithm::PerformHeldKarpAlgorithm(const Graph& graph) {
    std::vector<std::set<int>> sub_sets{ GenerateSubSets(graph.GetGraph().size()) };
}

std::vector<std::set<int>> HeldKarpAlgorithm::GenerateSubSets(int number_of_vertices) {
    std::vector<int> numbers(number_of_vertices);
    std::iota(numbers.begin(), numbers.end(), 1);
    std::vector<std::set<int>> sub_sets{};
    std::vector<int> result(number_of_vertices);

    auto sub_set_comparator{ [](const std::set<int>& a, const std::set<int>& b)
                             {
                                 return a.size() < b.size();
                             } };
    std::sort(sub_sets.begin(), sub_sets.end(), sub_set_comparator);
    return sub_sets;
}

void HeldKarpAlgorithm::GenerateCombination(const std::vector<int>& numbers,
            int start, int position, std::vector<std::set<int>>& sub_sets,
            std::vector<int>& result) {
    if (position == numbers.size()) {
        return;
    }

    std::set<int> set{ result.begin(), result.begin() + position };
    sub_sets.push_back(set);
    for (int i{ start }; i < numbers.size(); ++i) {
        result[position] = numbers[i];
        GenerateCombination(numbers, i + 1, position + 1, sub_sets, result);
    }
}
}// namespace s21
