cmake_minimum_required(VERSION 3.21)
project(Heightmap)

set(CMAKE_CXX_STANDARD 14)

add_executable(Heightmap main.cpp quadtree.cpp quadtree.h)
