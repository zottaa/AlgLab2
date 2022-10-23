cmake_minimum_required(VERSION 3.19.2)
project(Alglab2)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
add_executable(AlgLab2 main.cpp BinarySearchTree.h)

target_link_libraries(AlgLab2 gtest gtest_main)