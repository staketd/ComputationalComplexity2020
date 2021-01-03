cmake_minimum_required(VERSION 3.16)
project(ComputationalComplexity2020)
set(CMAKE_CXX_STANDARD 20)

include_directories(graph)
include_directories(.)
include_directories(edge_set)

set(
        SOURCES
        Edge.h
        edge_set/edge_set.cpp
        graph/graph.cpp
        path/path.cpp
        main.cpp
)

add_executable(main ${SOURCES})


