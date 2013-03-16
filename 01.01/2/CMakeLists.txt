cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(2)
set(CMAKE_CXX_FLAGS "-std=c++11")
add_executable(2 main.cpp)

install(TARGETS 2 RUNTIME DESTINATION bin)
