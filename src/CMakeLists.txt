cmake_minimum_required(VERSION 3.8)
project(seg)

set(CMAKE_CXX_STANDARD 11)

#add_subdirectory(utils)

set(treeNode treeNode.h)
set(kdTree kdTree.cpp)
set(utils utils.cpp)

add_library(kd_tree ${treeNode} ${kdTree} ${utils})

#target_link_libraries(kd_tree kdTreeUtils)