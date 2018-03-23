cmake_minimum_required(VERSION 3.8)
project(seg)

set(CMAKE_CXX_STANDARD 11)

set(treeNode treeNode.h)
set(kdTree kdTree.cpp)

add_library(kd_tree ${treeNode} ${kdTree})
