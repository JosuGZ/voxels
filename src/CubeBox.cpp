#include "CubeBox.h"

#include <iostream>

using namespace std;

cubeBox::cubeBox(int x, int y, int z): x(x), y(y), z(z) {
  changed = false;
}

cubeBox::cubeBox(const cubeBox& c): x(c.x), y(c.y), z(c.z) {
  changed=false;
  for(set<cube>::iterator i = c.cubes.begin(); i!=c.cubes.end(); i++)
    cubes.insert(*i);
  for(vector<float>::const_iterator j=c.cVertex.begin(); j!=c.cVertex.end();j++)
    cVertex.push_back(*j);
  for(vector<float>::const_iterator k=c.cNormal.begin(); k!=c.cNormal.end();k++)
    cNormal.push_back(*k);
}

cubeBox::~cubeBox() {}

void cubeBox::addCube(int x, int y, int z, int type) {
  cube temp(x,y,z,type);
  if (cubes.find(temp) == cubes.end()) {
    cubes.insert(temp);
    changed=true;
  }
}

void cubeBox::removeCube(int x, int y, int z) {
  cube temp(x,y,z);
  if (cubes.find(temp) != cubes.end()) {
    cubes.erase(temp);
    changed=true;
  }
}

bool cubeBox::collision(float x, float y, float z) const {
  cube temp((int)x,(int)y,(int)z);
  set<cube>::iterator i = cubes.find(temp);
  if (i!=cubes.end()) {
    return true;
  }  else {
    return false;
  }
}

bool cubeBox::collision(
  float left, float right, float down, float up, float _far, float _near
) const {
  set<cube>::iterator i;

  for (i=cubes.begin(); i!=cubes.end(); i++) {
    if ( !((*i).x > right || (*i).x+1 < left) )
      if( !((*i).y > up || (*i).y+1 < down) )
        if ( !((*i).z > _near || (*i).z+1 < _far) )
          return true;
  }

  return false;
}

const cube* cubeBox::find(int x, int y, int z) const {
  cube temp(x,y,z);
  set<cube>::iterator i = cubes.find(temp);
  if(i!=cubes.end())
    return &(*i);
  else
    return NULL;
}

bool cubeBox::operator==(const cubeBox& c) const {
  return x==c.x && y==c.y && z==c.z;
}

bool cubeBox::operator<(const cubeBox& c) const {
  return x == c.x ? (y == c.y ? (z < c.z) : (y < c.y)) : (x < c.x);
}
