cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)

set(treeNode treeNode.cpp)
aux_source_directory(. DIR_LIB_SRCS)

add_library(kd_tree ${treeNode})