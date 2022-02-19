cmake_minimum_required(VERSION 3.21)
project(heightmap)

set(CMAKE_CXX_STANDARD 14)

add_library (heightmap src/heightmap.cpp)
target_include_directories(heightmap PUBLIC include)
