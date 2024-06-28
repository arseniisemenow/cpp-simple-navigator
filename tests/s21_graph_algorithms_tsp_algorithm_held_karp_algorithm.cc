#include <gtest/gtest.h>

#include <algorithm>

#include "GraphAlgorithms/TSPAlgorithms/HeldKarpAlgorithm/HeldKarpAlgorithm.h"
#include "constants.h"

namespace s21 {
class GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest : public ::testing::Test {
 protected:
    void SetUp() override {}
    HeldKarpAlgorithm tsp_algorithm_{};
    Graph graph_{};
};

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, HeldKarpResultTest0) {
    graph_.LoadGraphFromFile(constants::kFileNames[0]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, 253);
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, HeldKarpResultTest1) {
    graph_.LoadGraphFromFile(constants::kFileNames[1]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, std::numeric_limits<int>::max());
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, HeldKarpResultTest2) {
    graph_.LoadGraphFromFile(constants::kFileNames[2]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, std::numeric_limits<int>::max());
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, HeldKarpResultTest3) {
    graph_.LoadGraphFromFile(constants::kFileNames[3]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, std::numeric_limits<int>::max());
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, HeldKarpResultTest4) {
    graph_.LoadGraphFromFile(constants::kFileNames[4]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, std::numeric_limits<int>::max());
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, HeldKarpResultTest5) {
    graph_.LoadGraphFromFile(constants::kFileNames[5]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, std::numeric_limits<int>::max());
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, HeldKarpResultTest6) {
    graph_.LoadGraphFromFile(constants::kFileNames[6]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, std::numeric_limits<int>::max());
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, HeldKarpResultTest7) {
    graph_.LoadGraphFromFile(constants::kFileNames[7]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, 8);
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, HeldKarpResultTest8) {
    graph_.LoadGraphFromFile(constants::kFileNames[8]);

    auto [vertices, distance]{ tsp_algorithm_.SolveTravelingSalesmanProblem(graph_) };

    ASSERT_EQ(distance, 27);
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, GenerateSubSetsTest) {
    tsp_algorithm_.GenerateSubSets(3);

    std::vector<std::set<int>> expected_sub_sets{
        {}, {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}
    };

    std::sort(expected_sub_sets.begin(), expected_sub_sets.end());
    std::sort(tsp_algorithm_.sub_sets_.begin(), tsp_algorithm_.sub_sets_.end());

    EXPECT_EQ(tsp_algorithm_.sub_sets_, expected_sub_sets);
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, GenerateCombinationTest) {
    std::vector<int> numbers{1, 2, 3};
    std::vector<int> result(3);
    tsp_algorithm_.GenerateCombination(numbers, 0, 0, result);

    std::vector<std::set<int>> expected_combinations{
        {}, {1}, {1, 2}, {1, 3}, {2}, {2, 3}, {3}
    };

    EXPECT_EQ(tsp_algorithm_.sub_sets_, expected_combinations);
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, GetCostSoFarTest) {
    std::set<int> set{1, 2};
    int previous_vertex{ 2 };

    std::set<int> empty_set{};
    std::set<int> set_1{1};
    std::set<int> set_12{1, 2};

    tsp_algorithm_.min_cost_map_[HeldKarpAlgorithm::Index{1, empty_set}] = 10;
    tsp_algorithm_.min_cost_map_[HeldKarpAlgorithm::Index{2, set_1}] = 20;
    tsp_algorithm_.min_cost_map_[HeldKarpAlgorithm::Index{3, set_12}] = 30;

    int cost{ tsp_algorithm_.GetCostSoFar(set, previous_vertex) };

    EXPECT_EQ(cost, 20);
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, IterateThroughSubSetsTest) {
    std::vector<std::vector<int>> distances{
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    int number_of_vertices{ 4 };

    tsp_algorithm_.GenerateSubSets(number_of_vertices - 1);
    tsp_algorithm_.IterateThroughSubSets(distances, number_of_vertices);

    int first{ tsp_algorithm_.min_cost_map_[HeldKarpAlgorithm::Index{1, {2, 3}}]};
    int second{ tsp_algorithm_.min_cost_map_[HeldKarpAlgorithm::Index{2, {1, 3}}]};
    int third{ tsp_algorithm_.min_cost_map_[HeldKarpAlgorithm::Index{3, {1, 2}}]};

    EXPECT_EQ(first, 70);
    EXPECT_EQ(second, 65);
    EXPECT_EQ(third, 75);
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, GetTotalCostTest) {
    std::vector<std::vector<int>> distances{
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    int number_of_vertices{ 4 };

    tsp_algorithm_.GenerateSubSets(number_of_vertices - 1);
    tsp_algorithm_.IterateThroughSubSets(distances, number_of_vertices);
    int total_cost{ tsp_algorithm_.GetTotalCost(distances, number_of_vertices) };

    EXPECT_EQ(total_cost, 80);
}

TEST_F(GraphAlgorithmsTspAlgorithmHeldKarpAlgorithmTest, GetPathTest) {
    std::vector<std::vector<int>> distances{
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    int number_of_vertices{ 4 };

    tsp_algorithm_.GenerateSubSets(number_of_vertices - 1);
    tsp_algorithm_.IterateThroughSubSets(distances, number_of_vertices);
    tsp_algorithm_.GetTotalCost(distances, number_of_vertices);

    std::vector<int> path{ tsp_algorithm_.GetPath(number_of_vertices) };

    std::vector<int> expected_path{0, 1, 3, 2, 0};

    EXPECT_EQ(path, expected_path);
}
} // namespace s21
