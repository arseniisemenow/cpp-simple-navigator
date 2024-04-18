#include "HeldKarpAlgorithm.h"

#include "common/structs.h"

#include <algorithm>
#include <numeric>
#include <limits>
#include <stack>

namespace s21 {
TspResult HeldKarpAlgorithm::SolveTravelingSalesmanProblem(const Graph &graph) {
    TspResult result{ PerformHeldKarpAlgorithm(graph) };
    return result;
}

TspResult HeldKarpAlgorithm::PerformHeldKarpAlgorithm(const Graph& graph) {
    TspResult result{};

    sub_sets_.clear();
    min_cost_map_.clear();
    parent_.clear();
    path_.clear();

    std::size_t number_of_vertices{ graph.GetGraph().size() };
    GenerateSubSets(number_of_vertices - 1);

    std::vector<std::vector<int>> distances{ graph.GetGraph() };
    IterateThroughSubSets(distances, number_of_vertices);

    result.distance = GetTotalCost(distances, number_of_vertices);
    result.vertices = GetPath(number_of_vertices);

    return result;
}

void HeldKarpAlgorithm::GenerateSubSets(int number_of_vertices) {
    std::vector<int> numbers(number_of_vertices);
    std::iota(numbers.begin(), numbers.end(), 1);
    std::vector<int> result(number_of_vertices);

    GenerateCombination(numbers, 0, 0, result);

    auto sub_set_comparator{ [](const std::set<int>& a, const std::set<int>& b)
                             {
                                 return a.size() < b.size();
                             } };
    std::sort(sub_sets_.begin(), sub_sets_.end(), sub_set_comparator);
}

void HeldKarpAlgorithm::GenerateCombination(const std::vector<int>& numbers,
            std::size_t start, std::size_t position,
            std::vector<int>& result) {
    if (position == numbers.size()) {
        return;
    }

    std::set<int> set{ result.begin(), result.begin() + position };
    sub_sets_.push_back(set);
    for (std::size_t i{ start }; i < numbers.size(); ++i) {
        result[position] = numbers[i];
        GenerateCombination(numbers, i + 1, position + 1, result);
    }
}

void HeldKarpAlgorithm::IterateThroughSubSets(
    const std::vector<std::vector<int>>& distances, int number_of_vertices) {
    for (const auto& set : sub_sets_) {
        int minimum_previous_vertex{ 0 };
        for (int current_vertex{ 1 };
             current_vertex < number_of_vertices;
             ++current_vertex) {
            if (set.find(current_vertex) != set.end()) {
                continue;
            }

            Index index{ static_cast<int>(current_vertex), set };
            int minimum_cost{ std::numeric_limits<int>::max() };

            for (int previous_vertex : set) {
                int cost{ distances[previous_vertex][current_vertex] +
                          GetCostSoFar(set, previous_vertex) };

                if (cost < minimum_cost) {
                    minimum_cost = cost;
                    minimum_previous_vertex = previous_vertex;
                }
            }

            if (set.empty()) {
                minimum_cost = distances[0][current_vertex];
            }

            min_cost_map_[index] = minimum_cost;
            parent_[index] = minimum_previous_vertex;
        }
    }
}

int HeldKarpAlgorithm::GetCostSoFar(const std::set<int>& set,
                                    int previous_vertex)
{
    std::set<int> set_copy{ set };
    set_copy.erase(previous_vertex);
    Index current_index{ previous_vertex, set_copy };
    int cost{ min_cost_map_.at(current_index) };
    set_copy.insert(previous_vertex);

    return cost;
}

int HeldKarpAlgorithm::GetTotalCost(const std::vector<std::vector<int>>& distances, int number_of_vertices)
{
    std::set<int> last_set{};
    for (int i{ 1 }; i < number_of_vertices; ++i) {
        last_set.insert(i);
    }

    int total_distance{ std::numeric_limits<int>::max() };
    int previous_vertex = -1;
    for (int vertex : last_set) {
        int cost{ distances[vertex][0] + GetCostSoFar(last_set, vertex) };
        if (cost < total_distance) {
            total_distance = cost;
            previous_vertex = vertex;
        }
    }

    parent_[Index{ 0, last_set }] = previous_vertex;

    return total_distance;
}

std::vector<int> HeldKarpAlgorithm::GetPath(int number_of_vertices) {
    std::vector<int> path{};

    std::set<int> set{};
    for (int i{ 0 }; i < number_of_vertices; ++i) {
        set.insert(i);
    }

    int start{ 0 };
    while (true) {
        path.push_back(start);
        set.erase(start);
        if (parent_.find(Index{ start, set }) == parent_.end()) {
            break;
        } else {
            start = parent_.at(Index{ start, set });
        }
    }

    return path;
}
}// namespace s21
