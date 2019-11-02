#include "cube.h"

#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>

using namespace std;

void drawCube() {
  /*float boxVertex[72] = {
    -0.5, 0, -0.5,
    0.5,0,-0.5,
    0.5,0,0.5,
    -0.5,0,0.5,
    -0.5, 1, -0.5,
    -0.5,1,0.5,
    0.5,1,0.5,
    0.5,1,-0.5,

    -0.5,1,-0.5,
    0.5, 1, -0.5,
    0.5,0,-0.5,
    -0.5, 0, -0.5,
    -0.5,1,0.5,
    -0.5, 0, 0.5,
    0.5,0,0.5,
    0.5,1,0.5,

    -0.5, 1, -0.5,
    -0.5,0,-0.5,
    -0.5, 0, 0.5,
    -0.5,1,0.5,
    0.5,1,-0.5,
    0.5,1,0.5,
    0.5,0,0.5,
    0.5,0,-0.5
  };*/

  float boxVertex[72] = {
    0, 0, 0,
    1,0,0,
    1,0,1,
    0,0,1,
    0, 1, 0,
    0,1,1,
    1,1,1,
    1,1,0,

    0,1,0,
    1, 1, 0,
    1,0,0,
    0, 0, 0,
    0,1,1,
    0, 0, 1,
    1,0,1,
    1,1,1,

    0, 1, 0,
    0,0,0,
    0, 0, 1,
    0,1,1,
    1,1,0,
    1,1,1,
    1,0,1,
    1,0,0
  };

  float boxTextureCord[48] = {
    0,0,
    1,0,
    1,1,
    0,1,
    0,0,
    0,1,
    1,1,
    1,0,

    0,1,
    1,1,
    1,0,
    0,0,
    0,1,
    0,0,
    1,0,
    1,1,

    1,0,
    0,0,
    0,1,
    1,1,
    1,0,
    1,1,
    0,1,
    0,0
  };

  float boxNormal[72] = {
    0,-1,0,
    0,-1,0,
    0,-1,0,
    0,-1,0,
    0,1,0,
    0,1,0,
    0,1,0,
    0,1,0,
    0,0,-1,
    0,0,-1,
    0,0,-1,
    0,0,-1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    -1,0,0,
    -1,0,0,
    -1,0,0,
    -1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0
  };

  /*unsigned short boxIndex[24] = {
    0,1,2,3,
    4,5,6,7,
    0,1,5,4,
    2,3,7,6,
    0,3,7,4,
    1,2,6,5
  };*/

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, boxVertex);
  glNormalPointer(GL_FLOAT, 0, boxNormal);
  glTexCoordPointer(2, GL_FLOAT, 0, boxTextureCord);

  glDrawArrays(GL_QUADS, 0, 24);
  //glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, boxIndex);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void drawFace(int face) {
  float boxVertex[72] = {
    0, 0, 0,
    1,0,0,
    1,0,1,
    0,0,1,
    0, 1, 0,
    0,1,1,
    1,1,1,
    1,1,0,

    0,1,0,
    1, 1, 0,
    1,0,0,
    0, 0, 0,
    0,1,1,
    0, 0, 1,
    1,0,1,
    1,1,1,

    0, 1, 0,
    0,0,0,
    0, 0, 1,
    0,1,1,
    1,1,0,
    1,1,1,
    1,0,1,
    1,0,0
  };

  float boxTextureCord[48] = {
    0,0,
    1,0,
    1,1,
    0,1,
    0,0,
    0,1,
    1,1,
    1,0,

    0,1,
    1,1,
    1,0,
    0,0,
    0,1,
    0,0,
    1,0,
    1,1,

    1,0,
    0,0,
    0,1,
    1,1,
    1,0,
    1,1,
    0,1,
    0,0
  };

  float boxNormal[72] = {
    0,-1,0,
    0,-1,0,
    0,-1,0,
    0,-1,0,
    0,1,0,
    0,1,0,
    0,1,0,
    0,1,0,
    0,0,-1,
    0,0,-1,
    0,0,-1,
    0,0,-1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    -1,0,0,
    -1,0,0,
    -1,0,0,
    -1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0
  };

  /*unsigned short boxIndex[24] = {
    0,1,2,3,
    4,5,6,7,
    0,1,5,4,
    2,3,7,6,
    0,3,7,4,
    1,2,6,5
  };*/

  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glColor4f(1,0,0,0.2);

  glVertexPointer(3, GL_FLOAT, 0, &boxVertex[face*12]);
  glNormalPointer(GL_FLOAT, 0, &boxNormal[face*12]);
  glTexCoordPointer(2, GL_FLOAT, 0, &boxTextureCord[face*8]);

  glDrawArrays(GL_QUADS, 0, 4);
  //glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, boxIndex);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
}

cube::cube() {
  x = y = z = type = 0;
}

cube::cube(const cube& c) {
  //cout << "Creando copia" << " : " << &c << " -> " << this << endl;
  x=c.x;
  y=c.y;
  z=c.z;
  type=c.type;
}

cube::cube(int x, int y, int z, int type): x(x), y(y), z(z), type(type){
  //cout << "Creando cubo (" << x << ", " << y << ", " << z << ")" << " : " << this << endl;
}

cube::~cube(){
  //cout << "Eliminando cubo (" << x << ", " << y << ", " << z << ")" << " : " << this << endl;
}

bool cube::operator<(const cube& c) const {
  return x == c.x ? (y == c.y ? (z < c.z) : (y < c.y)) : (x < c.x);
  return x<c.x ? true : x>c.x ? false : y<c.y ? true : y>c.y ? false : z<c.z ? true : false;
  cout << "Comparando cubos :" << this << " < " << &c << " : ";
  if (x<c.x){
    cout << "True" << endl;
    return true;
  }
  else
  {
    if (y<c.y){
      cout << "True" << endl;
      return true;
    }
    else{
      cout << (z<c.z ? "True" : "False") << endl;
      return z<c.z ? true : false;
    }
  }
}

/*bool cube::operator==(const cube& c) const {
  cout << "Comparando (==)" << endl;
  if (x==c.x && y==c.y && z==c.z)
    return true;
  else
    return false;
}

cube cube::operator=(const cube& c) {
  cout << "Creando copia" << endl;
  x=c.x;
  y=c.y;
  z=c.z;
  return *this;
}*/

void cube::draw() const {
  //cout << "Dibujando cubo (" << x << ", " << y << ", " << z << ")" << " : " << this << endl;
  //glDisable(GL_LIGHTING);
  //glDisable(GL_DEPTH_TEST);
  glColor4f(1,0,0,0.2);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef((float)x,(float)y,(float)z);
  drawCube();
}

void cube::drawHL() const {
  //cout << "Dibujando cubo (" << x << ", " << y << ", " << z << ")" << " : " << this << endl;
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glColor4f(1,0,0,0.5);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef((float)x,(float)y,(float)z);
  drawCube();
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
}

void cube::selFace(int face) const {
  //cout << "Dibujando cubo (" << x << ", " << y << ", " << z << ")" << " : " << this << endl;
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glColor4f(1,0,0,0.5);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef((float)x,(float)y,(float)z);
  drawFace(face);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
}
