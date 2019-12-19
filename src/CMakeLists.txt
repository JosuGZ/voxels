set(SOURCES
  engine/Engine.cpp
  graphics/graphic_functions.cpp
  Time.cpp
  CubeBox.cpp
  cube.cpp
  Game.cpp
)

add_executable(main main.cpp ${SOURCES})
target_link_libraries(
  main
  -static-libgcc
  -static-libstdc++
  -lopengl32
  -lglu32
  -lglew32
)
target_include_directories(
  main
  PRIVATE ../submodules/stb
  PRIVATE ../submodules/mingw-std-threads
)
set_target_properties(
  main PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ../dist/
)
