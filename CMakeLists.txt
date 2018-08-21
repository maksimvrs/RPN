cmake_minimum_required(VERSION 3.12)
project(RPN)

set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY})

add_executable(RPN main.cpp src/RPN.cpp src/RPN.hpp)