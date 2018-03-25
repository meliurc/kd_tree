cmake_minimum_required(VERSION 3.8)
project(seg)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(kdTree)
add_subdirectory(segment)

add_library(kd_tree)

target_link_libraries(kd_tree kdTree segment)
