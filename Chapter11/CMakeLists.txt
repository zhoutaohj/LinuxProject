# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (ThreadTest)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)


# 指定生成目标
add_executable(ThreadTest ${DIR_SRCS})

# 添加链接库
target_link_libraries(ThreadTest pthread)

add_definitions("-Wall -g")
