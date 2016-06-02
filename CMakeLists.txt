cmake_minimum_required(VERSION 2.6)
project(skiplist)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES test/main.cpp skiplist.hpp)
add_executable(skiplist ${SOURCE_FILES})