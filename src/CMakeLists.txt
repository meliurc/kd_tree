cmake_minimum_required(VERSION 3.8)
project(seg)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(kdTree)

set(readpnm pnmfile.h)
set(image image.h)
set(misc misc.h)

add_library(Felzenszwalb ${readpnm} ${image} ${misc})

target_link_libraries(Felzenszwalb kdTree)
