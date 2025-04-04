cmake_minimum_required(VERSION 3.5)

project(intersect_segments)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES "src/*.cpp")

add_executable(intersect_segments ${SOURCES})

target_include_directories(intersect_segments PRIVATE include)
