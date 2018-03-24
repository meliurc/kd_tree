cmake_minimum_required(VERSION 3.8)
project(seg)

set(CMAKE_CXX_STANDARD 11)
aux_source_directory(. UTIL_DIR_SRCS)

add_library(kdTreeUtils ${UTIL_DIR_SRCS})
