cmake_minimum_required(VERSION 3.21)
project(heightmap)

set(CMAKE_CXX_STANDARD 14)

find_package(camel-euclid REQUIRED)

add_library (heightmap
        Point2D.cpp
        Point3D.cpp
        Boundary.cpp
        HeightmapNode.cpp
        QuadtreeNode.cpp
)
#add_dependencies(heightmap camel-euclid-vector)

#target_include_directories(heightmap PUBLIC ../include ${CMAKE_SOURCE_DIR}/includes)
target_include_directories(heightmap PUBLIC ../includes)
target_link_libraries(heightmap camel-euclid-vector)