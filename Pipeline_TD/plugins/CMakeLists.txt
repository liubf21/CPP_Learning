cmake_minimum_required(VERSION 3.5)

project(myplugin)

set(CMAKE_CXX_STANDARD 20)

# 指定头文件目录
# target_include_directories(myplugin PUBLIC ../include)
include_directories(../include)

# 指定构建动态链接库
add_library(myplugin1 SHARED
  plugin1.cpp
)
add_library(myplugin2 SHARED
  plugin2.cpp
)

# 设置输出路径
set_target_properties(myplugin1 myplugin2
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..
)

# 在 Windows 平台上，需要将输出文件的后缀名设置为 .dll
if(WIN32)
  set_target_properties(myplugin1 myplugin2
    PROPERTIES
    SUFFIX ".dll"
  )
endif()