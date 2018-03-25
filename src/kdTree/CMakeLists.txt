cmake_minimum_required(VERSION 3.8)
project(seg)

set(CMAKE_CXX_STANDARD 11)

set(treeNode treeNode.h)
set(kdTree kdTree.cpp)
set(maxHeap maxHeap.h)
set(searchKNN searchKNN.h)
set(utils utils.h)

add_library(kdTree ${treeNode} ${kdTree} ${maxHeap} ${searchKNN} ${utils})