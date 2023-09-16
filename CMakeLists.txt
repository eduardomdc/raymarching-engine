cmake_minimum_required(VERSION 3.26)
project(metaballs)

find_package(SDL2 2.28.1 REQUIRED)

find_package(OpenMP)

include_directories(${SDL2_INCLUDE_DIRS})

set(MY_SOURCES
    src/main.cpp
    src/metaballs.cpp
    src/isosurface.cpp
    src/geometry.cpp
    src/draw.cpp
)

add_executable(metaballs ${MY_SOURCES})

target_link_libraries(metaballs PUBLIC ${SDL2_LIBRARIES} OpenMP::OpenMP_CXX)
