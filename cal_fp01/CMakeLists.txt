cmake_minimum_required(VERSION 3.13)
project(TP1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${PROJECT_SOURCE_DIR}/../include/")

file(GLOB_RECURSE SRC "src/*.cpp")

add_executable(TP1 ${SRC})
