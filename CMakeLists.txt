cmake_minimum_required(VERSION 3.28)
project(A2_SimpleNavigator_v1_0_CPP_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(A2_SimpleNavigator_v1_0_CPP_1
        src/Graph/Graph.cc
        src/Graph/Graph.h
        src/GraphAlgorithms/GraphAlgorithms.cc
        src/GraphAlgorithms/GraphAlgorithms.h
        src/Vertex/Vertex.cc
        src/Vertex/Vertex.h
        src/containers/adaptors/Queue/Queue.h
        src/containers/adaptors/Stack/Stack.h
        src/containers/sequence/List/List.h
        src/MatrixPath/MatrixMath.cc
        src/MatrixPath/MatrixMath.h
)
