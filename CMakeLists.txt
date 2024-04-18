cmake_minimum_required(VERSION 3.22)
project(A2_SimpleNavigator_v1_0_CPP_1)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

set(GRAPH_SOURCES
        src/Graph/Graph.cc
        src/Graph/Graph.h
)

set(HELD_KARP_SOURCES
        src/GraphAlgorithms/TSPAlgorithms/HeldKarpAlgorithm/HeldKarpAlgorithm.cc
        src/GraphAlgorithms/TSPAlgorithms/HeldKarpAlgorithm/HeldKarpAlgorithm.h
)
set(ALGORITHM_2_SOURCES
        src/GraphAlgorithms/TSPAlgorithms/Algorithm2/Algorithm2.cc
        src/GraphAlgorithms/TSPAlgorithms/Algorithm2/Algorithm2.h
)
set(COLONY_ALGORITHM_SOURCES
        src/GraphAlgorithms/TSPAlgorithms/ColonyAlgorithm/ColonyAlgorithm.cc
        src/GraphAlgorithms/TSPAlgorithms/ColonyAlgorithm/ColonyAlgorithm.h
)
set(GRAPH_ALGORITHMS_SOURCES
        src/GraphAlgorithms/GraphAlgorithms.cc
        src/GraphAlgorithms/GraphAlgorithms.h
        ${ALGORITHM_1_SOURCES}
        ${ALGORITHM_2_SOURCES}
        ${COLONY_ALGORITHM_SOURCES}
)
set(CONTAINERS_SOURCES
        src/containers/adaptors/Queue/Queue.h
        src/containers/adaptors/Stack/Stack.h
        src/containers/sequence/List/List.h)

set(COMMON_TEST_SOURCES
        tests/tests.cc)
set(GRAPH_TEST_SOURCES
        tests/s21_graph_tests.cc)
set(GRAPH_ALGORITHMS_TEST_SOURCES
        tests/s21_graph_algorithms_tests.cc
        tests/s21_graph_algorithms_search_engine_tests.cc
        tests/s21_graph_algorithms_shortest_path_engine.cc
        tests/s21_graph_algorithms_tsp_algorithms_tests.cc
)

set(COMMON_SOURCES
        src/common/structs.h
)

add_executable(s21_graph_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${CONTAINERS_SOURCES}
        ${COMMON_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_TEST_SOURCES}
)
add_executable(s21_graph_algorithms_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${CONTAINERS_SOURCES}
        ${COMMON_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_TEST_SOURCES}
)

add_executable(s21_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${CONTAINERS_SOURCES}
        ${COMMON_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_TEST_SOURCES}
)

target_link_libraries(s21_graph_algorithms_test gtest_main s21_graph s21_graph_algorithms)
target_link_libraries(s21_graph_test gtest_main s21_graph s21_graph_algorithms)
target_link_libraries(s21_test gtest_main s21_graph s21_graph_algorithms)

add_library(s21_graph STATIC
    ${GRAPH_SOURCES}
    ${COMMON_SOURCES}
)

add_library(s21_graph_algorithms STATIC
        ${GRAPH_ALGORITHMS_SOURCES}
        ${HELD_KARP_SOURCES}
        ${ALGORITHM_2_SOURCES}
        ${COLONY_ALGORITHM_SOURCES}
        ${COMMON_SOURCES}
        src/GraphAlgorithms/SearchEngine/SearchEngine.cc
        src/GraphAlgorithms/SearchEngine/SearchEngine.h
        src/GraphAlgorithms/ShortestPathEngine/DijkstraEngine/DijkstraEngine.cc
        src/GraphAlgorithms/ShortestPathEngine/FloydWarshallEngine/FloydWarshallEngine.cc
        src/GraphAlgorithms/ShortestPathEngine/ShortestPathEngine.cc
)

#todo: make Stack as static lib
#todo: make Queue as static lib
