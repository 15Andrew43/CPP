cmake_minimum_required(VERSION 3.14)
project(unique_ptr)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(GoogleTestDemo)

add_executable(unique_ptr main.cpp unique_ptr.h)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)