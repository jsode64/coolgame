cmake_minimum_required(VERSION 3.16)
project(coolgame)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib)

file(GLOB SOURCES "src/*.cpp" "src/fighters/*.cpp" "src/tiles/*.cpp")
add_executable(coolgame ${SOURCES})
add_compile_options(-Wall -Wextra)

target_link_libraries(coolgame PRIVATE raylib)
target_include_directories(coolgame PRIVATE inc)
