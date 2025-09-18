cmake_minimum_required(VERSION 3.16)
project(coolgame)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib)

add_executable(coolgame src/main.cpp src/player.cpp src/stage.cpp)
target_link_libraries(coolgame PRIVATE raylib)
target_include_directories(coolgame PRIVATE inc)
