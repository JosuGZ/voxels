set(SOURCES
  graphics/graphic_functions.cpp
  Time.cpp
  cube.cpp
  Game.cpp
)

add_executable(main main.cpp ${SOURCES})
target_link_libraries(main -lopengl32 -lglu32 corona.dll)
set_target_properties(
  main PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ../dist/
)
