cmake_minimum_required(VERSION 3.14)
project(comparison_of_sorts)

set(CMAKE_CXX_STANDARD 14)

add_executable(comparison_of_sorts main.cpp ShakerSort.h QuickSort.h)