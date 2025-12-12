cmake_minimum_required(VERSION 3.16)
project(coolgame)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib)

file(GLOB SOURCES "src/*.cpp" "src/fighters/*.cpp" "src/tiles/*.cpp")
add_executable(coolgame ${SOURCES})
add_compile_options(-Wall -Wextra -Werror -Wpedantic)

target_link_libraries(coolgame PRIVATE raylib)
target_include_directories(coolgame PRIVATE inc)

# Link macOS frameworks required by Raylib
if(APPLE)
    target_link_libraries(coolgame PRIVATE "-framework Foundation" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()
