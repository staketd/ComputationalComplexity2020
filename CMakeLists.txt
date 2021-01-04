cmake_minimum_required(VERSION 3.16)
project(ComputationalComplexity2020)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(graph)
include_directories(.)
include_directories(edge_set)

set(
        SOURCES
        Edge.h
        edge_set/edge_set.cpp
        path_set/path_set.cpp
        graph/graph.cpp
        path/path.cpp
        edge_set_generator/main_edge_set_generator.cpp
)

add_executable(TSPMain ${SOURCES} TSPApproxMain.cpp )
add_executable(CorrectMain ${SOURCES} CorrectMain.cpp)
add_executable(GeneratorMain test_generator/test_generator.cpp test_generator_main.cpp)
add_executable(Checker ${SOURCES} Checker.cpp)


