cmake_minimum_required(VERSION 3.0)
project(main)

# g++ -o server -g -O muduo_server.cpp xxx.cpp -I/usr/include -L/usr/lib -lmuduo_net -lmuduo_base -lpthread

# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置头文件搜索路径
# include_directories()
# 配置库文件搜索类路径
# link_directories()

# 设置需要编译的源文件列表
set(SRC_LIST muduo_server.cpp)

# 设置可执行文件最终存放路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


# 把指定路径下的所有源文件名字放入变量名SRC_LIST里面
# aux_source_directory(. SRC_LIST)


# 由SRC_LIST变量定义的源文件编译而来，生成可执行文件server
add_executable(server ${SRC_LIST})

# 表示server目标程序需要链接muduo_net, muduo_base, pthread这三个库文件
target_link_libraries(server muduo_net muduo_base pthread)