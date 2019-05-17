cmake_minimum_required(VERSION 3.13)
project(TP5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/../include/)

set(SRC src/Graph.h src/MutablePriorityQueue.h src/Test.cpp)

add_executable(TP5 ${SRC})

target_include_directories(TP5 PRIVATE ${Boost_INCLUDE_DIRS})
