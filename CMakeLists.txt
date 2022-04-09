cmake_minimum_required(VERSION 3.21)
project(Heightmap)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(heightmap)
add_executable (Heightmap main.cpp)
target_link_libraries(Heightmap PUBLIC heightmap)

#[[
add_executable (HeightmapNode main.cpp)
target_link_libraries(HeightmapNode PUBLIC heightmap)
target_link_directories(HeightmapNode PUBLIC heightmap/build)
target_include_directories(HeightmapNode PUBLIC heightmap/include)
]]
