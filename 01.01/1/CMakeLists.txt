cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(1)
set(CMAKE_CXX_FLAGS "-std=c++11")
add_executable(1 main.cpp)

install(TARGETS 1 RUNTIME DESTINATION bin)
