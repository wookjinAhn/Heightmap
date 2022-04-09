cmake_minimum_required(VERSION 3.21)
project(heightmap)

set(CMAKE_CXX_STANDARD 14)

add_library (heightmap
    src/Point2D.cpp
    src/Point3D.cpp
    src/Boundary.cpp
    src/HeightmapNode.cpp
    src/QuadtreeNode.cpp
)

target_include_directories(heightmap PUBLIC include)
