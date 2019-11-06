#include "cube.h"

#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>

#include "graphics/graphic_functions.h"

using namespace std;

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
