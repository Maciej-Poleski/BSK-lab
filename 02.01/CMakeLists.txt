cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(02.01)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(02.01 main.cpp)

install(TARGETS 02.01 RUNTIME DESTINATION bin)
