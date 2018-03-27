cmake_minimum_required(VERSION 3.8)

project(seg)

aux_source_directory(. DIR_SRCS)

# 添加 math 子目录
add_subdirectory(src)

# 指定生成目标
add_executable(seg ${DIR_SRCS})

# 添加链接库
target_link_libraries(seg Felzenszwalb)