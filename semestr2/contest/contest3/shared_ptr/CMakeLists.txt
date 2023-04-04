cmake_minimum_required(VERSION 3.14)
project(shared_ptr)

set(CMAKE_CXX_STANDARD 17)

#target_include_directories (shared_ptr PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

add_subdirectory(GoogleTestDemo)

add_executable(shared_ptr main.cpp shared_ptr.h)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)