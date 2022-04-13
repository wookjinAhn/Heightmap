cmake_minimum_required(VERSION 3.21)
project(Heightmap)

set(CMAKE_CXX_STANDARD 14)

find_package(camel-euclid REQUIRED)

add_subdirectory(heightmap/src)
add_executable (Heightmap main.cpp)
target_link_libraries(Heightmap heightmap camel-euclid-vector)

#[[
add_executable (HeightmapNode main.cpp)
target_link_libraries(HeightmapNode PUBLIC heightmap)
target_link_directories(HeightmapNode PUBLIC heightmap/build)
target_include_directories(HeightmapNode PUBLIC heightmap/include)
]]
