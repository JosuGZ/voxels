cmake_minimum_required (VERSION 2.6)
project (Voxels)

SET(CMAKE_BINARY_DIR build)
SET(CMAKE_CXX_FLAGS)
add_compile_options(-std=c++17 -v -Wall -Wextra -pedantic -Wno-comment)
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}")

add_subdirectory(src)

configure_file(tMinecraft.bmp dist/tMinecraft.bmp COPYONLY)
