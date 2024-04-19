cmake_minimum_required(VERSION 3.22)
project(A2_SimpleNavigator_v1_0_CPP_1 LANGUAGES CXX)
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(libs)

set(CONTAINERS_SOURCES
        src/containers/adaptors/Queue/Queue.h
        src/containers/adaptors/Stack/Stack.h
        src/containers/sequence/List/List.h
        src/containers/foo.cc
)

set(GRAPH_SOURCES
        src/Graph/Graph.cc
        src/Graph/Graph.h
)

set(SEARCH_ENGINE_SOURCES
    src/GraphAlgorithms/SearchEngine/SearchEngine.cc
    src/GraphAlgorithms/SearchEngine/SearchEngine.h
)

set(SHORTEST_PATH_ENGINE
    src/GraphAlgorithms/ShortestPathEngine/ShortestPathEngine.cc
    src/GraphAlgorithms/ShortestPathEngine/ShortestPathEngine.h
    src/GraphAlgorithms/ShortestPathEngine/DijkstraEngine/DijkstraEngine.cc
    src/GraphAlgorithms/ShortestPathEngine/DijkstraEngine/DijkstraEngine.h
    src/GraphAlgorithms/ShortestPathEngine/FloydWarshallEngine/FloydWarshallEngine.cc
    src/GraphAlgorithms/ShortestPathEngine/FloydWarshallEngine/FloydWarshallEngine.h
)
set(LEAST_SPANNING_TREE_ENGINE
    src/GraphAlgorithms/LeastSpanningTreeEngine/LeastSpanningTreeEngine.cc
    src/GraphAlgorithms/LeastSpanningTreeEngine/LeastSpanningTreeEngine.h
)

set(HELD_KARP_ALGORITHM_SOURCES
        src/GraphAlgorithms/TSPAlgorithms/HeldKarpAlgorithm/HeldKarpAlgorithm.cc
        src/GraphAlgorithms/TSPAlgorithms/HeldKarpAlgorithm/HeldKarpAlgorithm.h
)
set(GENETIC_ALGORITHM_SOURCES
        src/GraphAlgorithms/TSPAlgorithms/GeneticAlgorithm/GeneticAlgorithm.cc
        src/GraphAlgorithms/TSPAlgorithms/GeneticAlgorithm/GeneticAlgorithm.h
)
set(COLONY_ALGORITHM_SOURCES
        src/GraphAlgorithms/TSPAlgorithms/ColonyAlgorithm/ColonyAlgorithm.cc
        src/GraphAlgorithms/TSPAlgorithms/ColonyAlgorithm/ColonyAlgorithm.h
)
set(GRAPH_ALGORITHMS_SOURCES
        src/GraphAlgorithms/GraphAlgorithms.cc
        src/GraphAlgorithms/GraphAlgorithms.h
        ${SEARCH_ENGINE_SOURCES}
        ${SHORTEST_PATH_ENGINE}
        ${LEAST_SPANNING_TREE_ENGINE}
        ${HELD_KARP_ALGORITHM_SOURCES}
        ${GENETIC_ALGORITHM_SOURCES}
        ${COLONY_ALGORITHM_SOURCES}
)

set(GRAPH_ALGORITHMS_SEARCH_ENGINE_TEST_SOURCES
        tests/s21_graph_algorithms_search_engine_tests.cc)
set(GRAPH_ALGORITHMS_SHORTEST_PATH_ENGINE_TEST_SOURCES
        tests/s21_graph_algorithms_shortest_path_engine.cc)
set(GRAPH_ALGORITHMS_LEAST_SPANNING_TREE_ENGINE_TEST_SOURCES
        tests/s21_graph_algorithms_least_spanning_tree_engine.cc)

set(GRAPH_ALGORITHMS_TSP_ALGORITHM_COLONY_ALGORITHM
        tests/s21_graph_algorithms_tsp_algorithm_colony_algorithm.cc
)
set(GRAPH_ALGORITHMS_TSP_ALGORITHM_HELD_CARP_ALGORITHM
        tests/s21_graph_algorithms_tsp_algorithm_held_karp_algorithm.cc
)
set(GRAPH_ALGORITHMS_TSP_ALGORITHM_GENETIC_ALGORITHM
        tests/s21_graph_algorithms_tsp_algorithm_genetic_algorithm.cc
)

set(COMMON_TEST_SOURCES
        tests/tests.cc)
set(GRAPH_TEST_SOURCES
        tests/s21_graph_tests.cc)


set(COMMON_SOURCES
        src/common/structs.h
        src/common/constants.h
)

set(GRAPH_ALGORITHMS_TEST_SOURCES
        ${GRAPH_ALGORITHMS_SEARCH_ENGINE_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_SHORTEST_PATH_ENGINE_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_LEAST_SPANNING_TREE_ENGINE_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_TSP_ALGORITHM_COLONY_ALGORITHM}
        ${GRAPH_ALGORITHMS_TSP_ALGORITHM_HELD_CARP_ALGORITHM}
        ${GRAPH_ALGORITHMS_TSP_ALGORITHM_GENETIC_ALGORITHM}
)


add_executable(s21_graph_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${COMMON_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_TEST_SOURCES}
)
add_executable(s21_graph_algorithms_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${COMMON_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_TEST_SOURCES}
)
add_executable(s21_graph_algorithms_tsp_held_karp_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${COMMON_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_TSP_ALGORITHM_HELD_CARP_ALGORITHM}
)
add_executable(s21_graph_algorithms_tsp_colony_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${COMMON_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_TSP_ALGORITHM_COLONY_ALGORITHM}
)
add_executable(s21_graph_algorithms_tsp_genetic_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${COMMON_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_TSP_ALGORITHM_GENETIC_ALGORITHM}
)
add_executable(s21_graph_algorithms_search_engine_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${COMMON_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_SEARCH_ENGINE_TEST_SOURCES}
)
add_executable(s21_graph_algorithms_shortest_path_engine_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${COMMON_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_SHORTEST_PATH_ENGINE_TEST_SOURCES}
)
add_executable(s21_graph_algorithms_least_spanning_tree_engine_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${COMMON_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_LEAST_SPANNING_TREE_ENGINE_TEST_SOURCES}
)

add_executable(s21_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${COMMON_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_TEST_SOURCES}
)

add_executable(cli
    src/cli/main.cc
        ${GRAPH_ALGORITHMS_SOURCES}
        ${GRAPH_SOURCES}
        src/cli/MainMenu/MainMenu.cc
        src/cli/MainMenu/MainMenu.h
        src/cli/common/structs.h
        src/cli/Menu/menu.cc
        src/cli/Menu/menu.h
        src/cli/ChoiceOneMenu/ChoiceOneMenu.cc
        src/cli/ChoiceOneMenu/ChoiceOneMenu.h
        src/cli/common/constants.h
)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(cli s21_graph s21_graph_algorithms s21_containers ${CURSES_LIBRARIES})

target_link_libraries(s21_graph_algorithms_least_spanning_tree_engine_test gtest_main s21_graph s21_graph_algorithms s21_containers)
target_link_libraries(s21_graph_algorithms_shortest_path_engine_test gtest_main s21_graph s21_graph_algorithms s21_containers)
target_link_libraries(s21_graph_algorithms_search_engine_test gtest_main s21_graph s21_graph_algorithms s21_containers)
target_link_libraries(s21_graph_algorithms_tsp_genetic_test gtest_main s21_graph s21_graph_algorithms s21_containers)
target_link_libraries(s21_graph_algorithms_tsp_colony_test gtest_main s21_graph s21_graph_algorithms s21_containers)
target_link_libraries(s21_graph_algorithms_tsp_held_karp_test gtest_main s21_graph s21_graph_algorithms s21_containers)
target_link_libraries(s21_graph_algorithms_test gtest_main s21_graph s21_graph_algorithms s21_containers)
target_link_libraries(s21_graph_test gtest_main s21_graph s21_graph_algorithms s21_containers)
target_link_libraries(s21_test gtest_main s21_graph s21_graph_algorithms s21_containers)

add_library(s21_graph STATIC
    ${GRAPH_SOURCES}
    ${COMMON_SOURCES}
)

add_library(s21_graph_algorithms STATIC
        ${GRAPH_ALGORITHMS_SOURCES}
        ${COMMON_SOURCES}
)
add_library(s21_containers STATIC
        ${CONTAINERS_SOURCES}
)