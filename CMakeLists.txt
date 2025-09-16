project(coolgame)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

find_package(raylib)

add_executable(coolgame src/main.cpp)
target_link_libraries(coolgame PRIVATE raylib)
target_include_directories(coolgame PRIVATE inc)
