cmake_minimum_required(VERSION 3.13)
project(TP4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/../include/)

set(SRC src/Person.cpp src/Person.h src/Graph.h src/Test.cpp)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(TP4 ${SRC})
