cmake_minimum_required(VERSION 3.21)
project(Heightmap)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(heightmap)
add_executable (Heightmap main.cpp)
target_link_libraries(Heightmap PUBLIC heightmap)

#[[
add_executable (Heightmap main.cpp)
target_link_libraries(Heightmap PUBLIC heightmap)
target_link_directories(Heightmap PUBLIC heightmap/build)
target_include_directories(Heightmap PUBLIC heightmap/include)
]]
