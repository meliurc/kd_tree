cmake_minimum_required(VERSION 3.8)
project(seg)

set(CMAKE_CXX_STANDARD 11)

#add_subdirectory(utils)

set(treeNode treeNode.h)
set(kdTree kdTree.cpp)
set(maxHeap maxHeap.h)
set(searchKNN searchKNN.h)
set(utils utils.h)

add_library(kd_tree ${treeNode} ${kdTree} ${maxHeap} ${searchKNN} ${utils})

#target_link_libraries(kd_tree kdTreeUtils)