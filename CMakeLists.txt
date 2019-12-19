cmake_minimum_required (VERSION 2.6)
project (Voxels)

SET(CMAKE_BINARY_DIR build)
SET(CMAKE_CXX_FLAGS)
add_compile_options(-std=c++17 -v -Wall -Wextra -pedantic -Wno-comment)
LINK_DIRECTORIES(
  "${PROJECT_SOURCE_DIR}/lib/glew-2.1.0"
)
INCLUDE_DIRECTORIES(
  "${PROJECT_SOURCE_DIR}/lib/glew-2.1.0/include"
)

add_subdirectory(src)

configure_file(tMinecraft.bmp dist/tMinecraft.bmp COPYONLY)
configure_file(lib/glew-2.1.0/glew32.dll dist/glew32.dll COPYONLY)
