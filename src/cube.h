#ifndef CUBE_H
#define CUBE_H

void drawCube();
void drawFace(int face);

class cube {
public:
  int x, y, z, type;

  cube();
  cube(const cube& c);
  cube(int x, int y, int z, int type=0);
  ~cube();

  bool operator<(const cube& c) const;
  void draw() const;
  void drawHL() const;
  void selFace(int face) const;
};

#endif // CUBE_H
