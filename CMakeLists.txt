cmake_minimum_required(VERSION 3.26)
project(metaballs)

find_package(SDL2 2.28.1 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(MY_SOURCES
    src/main.cpp
    src/metaballs.cpp
)

add_executable(metaballs ${MY_SOURCES})

target_link_libraries(metaballs ${SDL2_LIBRARIES})
