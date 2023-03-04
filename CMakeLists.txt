cmake_minimum_required(VERSION 3.15.0)

project(ac_types)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(include)

add_subdirectory(test)

enable_testing()