cmake_minimum_required(VERSION 3.13)
project(TP10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/../include/)

file(GLOB_RECURSE SRC "src/*.cpp" "src/*.h")

add_executable(TP10 ${SRC})
