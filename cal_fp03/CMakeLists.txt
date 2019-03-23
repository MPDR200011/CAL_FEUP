cmake_minimum_required(VERSION 3.13)
project(TP3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/../include/)

file(GLOB_RECURSE SRC "src/*.cpp")
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(TP3 ${SRC})
target_link_libraries(TP3 Threads::Threads)
target_compile_options(TP3 PRIVATE -O3)
