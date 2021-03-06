#ifndef CUBEBOX_H
#define CUBEBOX_H

#include <GL/glew.h>
#include <GL/glu.h>
#include <set>
#include <vector>

#include "cube.h"

class cubeBox {
  std::set<cube> cubes;
  GLuint buffers[3];
  std::vector<float> cVertex;
  std::vector<float> cNormal;
  std::vector<float> cTexture;
  bool changed;
public:
  int x, y, z;

  void copyData();
  void buildGeometry();

  bool operator==(const cubeBox& c) const;
  bool operator<(const cubeBox& c) const;

  cubeBox(const cubeBox& c);
  cubeBox(int x, int y, int z);
  ~cubeBox();
  void addCube(int x, int y, int z, int type=0);
  void removeCube(int x, int y, int z);
  const cube* find(int x, int y, int z) const;
  void drawGeometry();
  bool collision(float x, float y, float z) const;
  bool collision(float left, float right, float down, float up, float _far, float _near) const;
};

#endif // CUBEBOX_H
