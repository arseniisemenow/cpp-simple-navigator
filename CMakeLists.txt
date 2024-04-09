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
set(GRAPH_ALGORITHMS_SOURCES
        src/GraphAlgorithms/GraphAlgorithms.cc
        src/GraphAlgorithms/GraphAlgorithms.h)
set(CONTAINERS_SOURCES
        src/containers/adaptors/Queue/Queue.h
        src/containers/adaptors/Stack/Stack.h
        src/containers/sequence/List/List.h)

set(COMMON_TEST_SOURCES
        tests/tests.cc)
set(GRAPH_TEST_SOURCES
        tests/s21_graph_tests.cc)
set(GRAPH_ALGORITHMS_TEST_SOURCES
        tests/s21_graph_algorithms_tests.cc)

set(ALGORITHM_1_SOURCES
        src/GraphAlgorithms/TSPAlgorithms/Algorithm1/Algorithm1.cc
        src/GraphAlgorithms/TSPAlgorithms/Algorithm1/Algorithm1.h
)
set(ALGORITHM_2_SOURCES
        src/GraphAlgorithms/TSPAlgorithms/Algorithm2/Algorithm2.cc
        src/GraphAlgorithms/TSPAlgorithms/Algorithm2/Algorithm2.h
)
set(COLONY_ALGORITHM_SOURCES
        src/GraphAlgorithms/TSPAlgorithms/ColonyAlgorithm/ColonyAlgorithm.cc
        src/GraphAlgorithms/TSPAlgorithms/ColonyAlgorithm/ColonyAlgorithm.h
)

add_executable(s21_graph_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${CONTAINERS_SOURCES}
        ${GRAPH_TEST_SOURCES}
)
add_executable(s21_graph_algorithms_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${CONTAINERS_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_TEST_SOURCES}
        src/GraphAlgorithms/TSPAlgorithms/Algorithm1/Algorithm1.cc
        src/GraphAlgorithms/TSPAlgorithms/Algorithm1/Algorithm1.h
        src/GraphAlgorithms/TSPAlgorithms/Algorithm2/Algorithm2.cc
        src/GraphAlgorithms/TSPAlgorithms/Algorithm2/Algorithm2.h
        src/GraphAlgorithms/TSPAlgorithms/ColonyAlgorithm/ColonyAlgorithm.cc
        src/GraphAlgorithms/TSPAlgorithms/ColonyAlgorithm/ColonyAlgorithm.h
        src/GraphAlgorithms/TSPAlgorithms/Algorithm1/Algorithm1.cc
)

add_executable(s21_test
        ${GRAPH_SOURCES}
        ${GRAPH_ALGORITHMS_SOURCES}
        ${CONTAINERS_SOURCES}
        ${COMMON_TEST_SOURCES}
        ${GRAPH_TEST_SOURCES}
        ${GRAPH_ALGORITHMS_TEST_SOURCES}
        src/common/structs.h
)

target_link_libraries(s21_graph_test gtest_main)
target_link_libraries(s21_graph_algorithms_test gtest_main)
target_link_libraries(s21_test gtest_main)