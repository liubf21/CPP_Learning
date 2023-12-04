cmake_minimum_required(VERSION 3.10)
project(ScoreManagement)

include_directories(include)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)
# SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(SRC_FILES src/main.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
# add_subdirectory(src)

# target_link_libraries(${PROJECT_NAME} myplugin)
