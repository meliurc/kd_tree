cmake_minimum_required(VERSION 3.8)
project(seg)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(kdTree)

#set(readpnm pnmfile.h)
#set(image image.h)
#set(misc misc.h)
#set(seg_img segment-image.h)
set(SEGMENT convolve.h disjoint-set.h filter.h image.h imconv.h imutil.h misc.h pnmfile.h segment-graph.h segment-image.h)

#aux_source_directory(. SEG_DIR_SRCS)

#add_library(Felzenszwalb ${readpnm} ${image} ${misc} ${seg_img})
add_library(Felzenszwalb ${SEGMENT})

target_link_libraries(Felzenszwalb kdTree)
