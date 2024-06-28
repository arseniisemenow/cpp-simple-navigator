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

    for (std::size_t i{ 0 }; i < distances.size(); ++i) {
        for (std::size_t j{ 0 }; j < distances[0].size(); ++j) {
            if (distances[i][j] == 0 && i != j) {
                distances[i][j] = std::numeric_limits<int>::max();
            }
        }
    }

    IterateThroughSubSets(distances, number_of_vertices);

    int total_cost{ GetTotalCost(distances, number_of_vertices) };
    if (total_cost == std::numeric_limits<int>::max()) {
        result.distance = std::numeric_limits<int>::max();
        result.vertices = {};
    } else {
        result.distance = total_cost;
        result.vertices = GetPath(number_of_vertices);
    }

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
    std::vector<std::vector<int>>& distances, int number_of_vertices) {
    for (const auto& set : sub_sets_) {
        for (int current_vertex{ 1 };
             current_vertex < number_of_vertices;
             ++current_vertex) {
            if (set.find(current_vertex) != set.end()) {
                continue;
            }

            Index index{ static_cast<int>(current_vertex), set };
            int minimum_cost{ std::numeric_limits<int>::max() };
            int minimum_previous_vertex{ -1 };

            for (int previous_vertex : set) {
                int cost_so_far{ GetCostSoFar(set, previous_vertex) };
                int cost{};
                if (distances[previous_vertex][current_vertex] ==
                        std::numeric_limits<int>::max() ||
                    cost_so_far == std::numeric_limits<int>::max()) {
                    cost = std::numeric_limits<int>::max();
                } else {
                    cost = distances[previous_vertex][current_vertex] + cost_so_far;
                }

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
    int cost{ min_cost_map_.count(current_index) ?
                min_cost_map_.at(current_index) :
                std::numeric_limits<int>::max() };

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
        int cost_so_far{ GetCostSoFar(last_set, vertex) };
        int cost{};
        if (distances[vertex][0] == std::numeric_limits<int>::max() ||
                cost_so_far == std::numeric_limits<int>::max()) {
            cost = std::numeric_limits<int>::max();
        } else {
            cost = distances[vertex][0] + cost_so_far;
        }

        if (cost < total_distance) {
            total_distance = cost;
            previous_vertex = vertex;
        }
    }

    if (previous_vertex == -1 ||
            total_distance == std::numeric_limits<int>::max()) {
        return std::numeric_limits<int>::max();
    }

    parent_[Index{ 0, last_set }] = previous_vertex;

    return total_distance;
}

std::vector<int> HeldKarpAlgorithm::GetPath(int number_of_vertices) {
    std::vector<int> path{};

    std::set<int> remaining_vertices{};
    for (int i{ 1 }; i < number_of_vertices; ++i) {
        remaining_vertices.insert(i);
    }

    int current_vertex{ 0 };
    path.push_back(current_vertex);

    while (!remaining_vertices.empty()) {
        Index index{current_vertex, remaining_vertices};
        if (parent_.count(index) == 0) {
            break;
        }

        int next_vertex{ parent_[index] };
        if (next_vertex == -1) {
            break;
        }

        path.push_back(next_vertex);
        remaining_vertices.erase(next_vertex);
        current_vertex = next_vertex;
    }

    path.push_back(0);
    return path;
}
} // namespace s21
