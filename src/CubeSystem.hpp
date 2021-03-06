#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <Math.h>

#include "engine/Engine.h"
#include "graphics/gl_utils.h"
#include "graphics/graphic_functions.h"
#include "Time.h"
#include "CubeBox.h"
#include "cube.h"

using namespace std;

float vertex[72] = {
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

float normal[72] = {
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

//int ntextures = 2;
/*float texture[48] = {
  0,0,
  0.5,0,
  0.5,1,
  0,1,
  0,0,
  0,1,
  0.5,1,
  0.5,0,

  0,1,
  0.5,1,
  0.5,0,
  0,0,
  0,1,
  0,0,
  0.5,0,
  0.5,1,

  0.5,0,
  0,0,
  0,1,
  0.5,1,
  0.5,0,
  0.5,1,
  0,1,
  0,0
};*/

float texture[48] = {
  7./16, 1./16,
  7./16, 0./16,
  8./16, 0./16,
  8./16, 1./16,
  7./16, 1./16,
  7./16, 0./16,
  8./16, 0./16,
  8./16, 1./16,
  7./16, 1./16,
  7./16, 0./16,
  8./16, 0./16,
  8./16, 1./16,
  7./16, 1./16,
  7./16, 0./16,
  8./16, 0./16,
  8./16, 1./16,
  7./16, 1./16,
  7./16, 0./16,
  8./16, 0./16,
  8./16, 1./16,
  7./16, 1./16,
  7./16, 0./16,
  8./16, 0./16,
  8./16, 1./16
};

/*float texture2[48] = {
  0.5,0,
  1,0,
  1,1,
  0.5,1,
  /*0,0,
  0,0.0625,
  0.0625,0.0625,
  0.0625,0,*/
  /*0,0,
  0,1./16,
  1./16,1./16,
  1./16,0,


  0.5,1,
  1,1,
  1,0,
  0.5,0,
  0.5,1,
  0.5,0,
  1,0,
  1,1,

  1,0,
  0.5,0,
  0.5,1,
  1,1,
  1,0,
  1,1,
  0.5,1,
  0.5,0
};*/

float texture2[48] = {
  1./16, 1./16,
  1./16, 0./16,
  2./16, 0./16,
  2./16, 1./16,
  1./16, 1./16,
  1./16, 0./16,
  2./16, 0./16,
  2./16, 1./16,
  1./16, 1./16,
  1./16, 0./16,
  2./16, 0./16,
  2./16, 1./16,
  1./16, 1./16,
  1./16, 0./16,
  2./16, 0./16,
  2./16, 1./16,
  1./16, 1./16,
  1./16, 0./16,
  2./16, 0./16,
  2./16, 1./16,
  1./16, 1./16,
  1./16, 0./16,
  2./16, 0./16,
  2./16, 1./16
};

float texture3[48] = {
  5./16, 1./16,
  5./16, 0./16,
  4./16, 0./16,
  4./16, 1./16,
  5./16, 1./16,
  5./16, 0./16,
  4./16, 0./16,
  4./16, 1./16,
  5./16, 1./16,
  5./16, 0./16,
  4./16, 0./16,
  4./16, 1./16,
  5./16, 1./16,
  5./16, 0./16,
  4./16, 0./16,
  4./16, 1./16,
  5./16, 1./16,
  5./16, 0./16,
  4./16, 0./16,
  4./16, 1./16,
  5./16, 1./16,
  5./16, 0./16,
  4./16, 0./16,
  4./16, 1./16
};

float tnt3[48] = {
  10./16, 0./16,
  10./16, 1./16,
  11./16, 1./16,
  11./16, 0./16,

  9./16, 0./16,
  9./16, 1./16,
  10./16, 1./16,
  10./16, 0./16,

  9./16, 0./16,
  8./16, 0./16,
  8./16, 1./16,
  9./16, 1./16,

  8./16, 0./16,
  8./16, 1./16,
  9./16, 1./16,
  9./16, 0./16,

  8./16, 0./16,
  8./16, 1./16,
  9./16, 1./16,
  9./16, 0./16,

  9./16, 0./16,
  8./16, 0./16,
  8./16, 1./16,
  9./16, 1./16
};

float tronco4[48] = {
  5./16, 1./16,
  5./16, 2./16,
  6./16, 2./16,
  6./16, 1./16,

  5./16, 1./16,
  5./16, 2./16,
  6./16, 2./16,
  6./16, 1./16,

  5./16, 1./16,
  4./16, 1./16,
  4./16, 2./16,
  5./16, 2./16,

  4./16, 1./16,
  4./16, 2./16,
  5./16, 2./16,
  5./16, 1./16,

  4./16, 1./16,
  4./16, 2./16,
  5./16, 2./16,
  5./16, 1./16,

  5./16, 1./16,
  4./16, 1./16,
  4./16, 2./16,
  5./16, 2./16
};

float sand5[48] = {
  2./16, 1./16,
  2./16, 2./16,
  3./16, 2./16,
  3./16, 1./16,

  2./16, 1./16,
  2./16, 2./16,
  3./16, 2./16,
  3./16, 1./16,

  3./16, 1./16,
  2./16, 1./16,
  2./16, 2./16,
  3./16, 2./16,

  2./16, 1./16,
  2./16, 2./16,
  3./16, 2./16,
  3./16, 1./16,

  2./16, 1./16,
  2./16, 2./16,
  3./16, 2./16,
  3./16, 1./16,

  3./16, 1./16,
  2./16, 1./16,
  2./16, 2./16,
  3./16, 2./16
};

void cubeBox::drawGeometry(){
  //cout << "Reconstruyendo geometr�a de cubeBox (" << x << ", " << y << ", " << z << ")" << " : " << this << endl;
  if (changed){
    changed=false;
    buildGeometry();
  }
  //glDisable(GL_LIGHTING);
  //glDisable(GL_DEPTH_TEST);
  //glColor4f(rand()%10*0.1,rand()%10*0.1,rand()%10*0.1,0.2);
  glColor4f(1,0,0,0.2);

  //glDisable(GL_LIGHTING);
  //glDisable(GL_DEPTH_TEST);
  //glDisable(GL_TEXTURE_2D);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER , buffers[0]);
  glVertexPointer(3, GL_FLOAT, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER , buffers[1]);
  glNormalPointer(GL_FLOAT, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
  glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDrawArrays(GL_QUADS, 0, cVertex.size()/3);
  //glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, boxIndex);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  //glEnable(GL_LIGHTING);
  //glEnable(GL_DEPTH_TEST);
  //glEnable(GL_TEXTURE_2D);
}

const int tCubeBox = 20;

typedef float v4[4];
typedef struct v4i {
  v4 v;
  cubeBox* i;
  bool operator<(const v4i& comp){
    return v[3]<comp.v[3];
  }
} v4i;

class cubeSystem{
  static bool init;
  static cubeSystem* CS;
  set<cubeBox> cubeBoxData;
  unsigned cubeCount;
  cubeSystem(){
    Engine::instance();
    //cubeCount=0;
  }
public:
  ~cubeSystem(){
    cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << endl << endl << endl;
    //init=false;
  }
  static cubeSystem* initCubeSystem(){
    if (!init)
    {
      cout << "Iniciando el sistema de cubos" << endl;
      CS = new cubeSystem;
      init=true;
      return CS;
    }
    else
      cout << "Not again :P" << endl;
  }
  static cubeSystem* getCubeSystem(){
    if (init)
      return CS;
    else
      return NULL;
  }
  void addCube(int x, int y, int z, int type=0){
    int cx=floor(x), cy=floor(y), cz=floor(z);
    cubeBox temp(floor((float)cx/tCubeBox),
            floor((float)cy/tCubeBox),
            floor((float)cz/tCubeBox));
    cubeBoxData.insert(temp);
    set<cubeBox>::iterator i = cubeBoxData.find(temp);
    const_cast<cubeBox&>(*i).addCube(cx,cy,cz,type);
  }
  void removeCube(int x, int y, int z){
    int cx=floor(x), cy=floor(y), cz=floor(z);
    cubeBox temp(floor((float)cx/tCubeBox),
            floor((float)cy/tCubeBox),
            floor((float)cz/tCubeBox));
    cubeBoxData.insert(temp);
    set<cubeBox>::iterator i = cubeBoxData.find(temp);
    const_cast<cubeBox&>(*i).removeCube(cx,cy,cz);


    cubeBox temp1(floor((float)cx/tCubeBox)-1,
            floor((float)cy/tCubeBox),
            floor((float)cz/tCubeBox));
    i = cubeBoxData.find(temp1);
    if (i != cubeBoxData.end())
      const_cast<cubeBox&>(*i).buildGeometry();
    cubeBox temp2(floor((float)cx/tCubeBox)+1,
            floor((float)cy/tCubeBox),
            floor((float)cz/tCubeBox));
    i = cubeBoxData.find(temp2);
    if (i != cubeBoxData.end())
      const_cast<cubeBox&>(*i).buildGeometry();
    cubeBox temp3(floor((float)cx/tCubeBox),
            floor((float)cy/tCubeBox)-1,
            floor((float)cz/tCubeBox));
    i = cubeBoxData.find(temp3);
    if (i != cubeBoxData.end())
      const_cast<cubeBox&>(*i).buildGeometry();
    cubeBox temp4(floor((float)cx/tCubeBox),
            floor((float)cy/tCubeBox)+1,
            floor((float)cz/tCubeBox));
    i = cubeBoxData.find(temp4);
    if (i != cubeBoxData.end())
      const_cast<cubeBox&>(*i).buildGeometry();
    cubeBox temp5(floor((float)cx/tCubeBox),
            floor((float)cy/tCubeBox),
            floor((float)cz/tCubeBox)-1);
    i = cubeBoxData.find(temp5);
    if (i != cubeBoxData.end())
      const_cast<cubeBox&>(*i).buildGeometry();
    cubeBox temp6(floor((float)cx/tCubeBox),
            floor((float)cy/tCubeBox),
            floor((float)cz/tCubeBox)+1);
    i = cubeBoxData.find(temp6);
    if (i != cubeBoxData.end())
      const_cast<cubeBox&>(*i).buildGeometry();
  }
  void drawAllCubes(float x, float y, float z, float aX, float aY){
    //cout << "Dibujando todos los cubos" << endl;
    v4i temp;
    vector<v4i> list;
    for (set<cubeBox>::iterator i=cubeBoxData.begin(); i!=cubeBoxData.end(); i++){
      if( pow((*i).x*tCubeBox-x,2) + pow((*i).z*tCubeBox-z,2) + pow((*i).y*tCubeBox-y,2) < pow(75,2) ){
        float zT=(*i).z*tCubeBox+tCubeBox-z;
        float xT=(*i).x*tCubeBox+tCubeBox-x;
        //if (xT>x)
          //if (zT>z)
          temp.v[3] = pow((*i).x*tCubeBox-x,2) + pow((*i).z*tCubeBox-z,2) + pow((*i).y*tCubeBox-y,2);
          temp.i = const_cast<cubeBox *>(&(*i));
          list.push_back(temp);
          //const_cast<cubeBox&>(*i).drawGeometry();
        /*else
          const_cast<cubeBox&>(*i).drawGeometry();*/
        /*if ( atan(((*i).z*tCubeBox+z)/((*i).x*tCubeBox+x))>aX-M_PI/2 &&
            atan(((*i).z*tCubeBox+z)/((*i).x*tCubeBox+x))<aX+M_PI/2 )
          const_cast<cubeBox&>(*i).drawGeometry();*/
          //i->drawAllCubes();
      }
    }
    sort(list.begin(), list.end());
    for (int j=0; j<list.size(); j++){
      list[j].i->drawGeometry();
    }
  }
  bool collision(float x, float y, float z) const {
    int cx=x>=0?x:(int)floor(x), cy=y>=0?y:(int)floor(y), cz=z>=0?z:(int)floor(z);
    cubeBox temp(cx/tCubeBox,cy/tCubeBox,cz/tCubeBox);
    set<cubeBox>::iterator i = cubeBoxData.find(temp);
    if(i!=cubeBoxData.end())
      return i->collision(cx,cy,cz);
    else
      return false;
  }
  const cube* find(int x, int y, int z) const {
    cubeBox temp(floor((float) x/tCubeBox),floor((float) y/tCubeBox),floor((float) z/tCubeBox));
    set<cubeBox>::iterator i = cubeBoxData.find(temp);
    if(i!=cubeBoxData.end())
      return i->find(x,y,z);
    else
      return NULL;
  }
  bool collision(float left, float right, float down, float up, float _far, float _near) const {

    set<cubeBox>::iterator i;

    for (i=cubeBoxData.begin(); i!=cubeBoxData.end(); i++)
    {
      //f ( !((*i).x*tCubeBox > right || (*i).x*tCubeBox+tCubeBox < left) )
        //if( !((*i).y*tCubeBox > up || (*i).y*tCubeBox+tCubeBox < down) )
          //if ( !((*i).z*tCubeBox > _near || (*i).z*tCubeBox+tCubeBox < _far) )
      /*if( (*i).x*tCubeBox > down && (*i).x*tCubeBox+tCubeBox < up &&
        (*i).y*tCubeBox > left && (*i).y*tCubeBox+tCubeBox < right &&
        (*i).z*tCubeBox > _far && (*i).z*tCubeBox+tCubeBox < _near )*/
      if ( !((*i).x*tCubeBox > right || (*i).x*tCubeBox+tCubeBox < left) )
        if( !((*i).y*tCubeBox > up || (*i).y*tCubeBox+tCubeBox < down) )
          if ( !((*i).z*tCubeBox > _near || (*i).z*tCubeBox+tCubeBox < _far) )
            if(i->collision(left, right, down, up, _far, _near))
              return true;
    }

    return false;

  }
};
bool cubeSystem::init=false;
cubeSystem* cubeSystem::CS=NULL;

void cubeBox::copyData() {
  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER, cVertex.size() * sizeof(float), 0, GL_DYNAMIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, cVertex.size() * sizeof(float), &cVertex[0]);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
  glBufferData(GL_ARRAY_BUFFER, cNormal.size() * sizeof(float), 0, GL_DYNAMIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, cNormal.size() * sizeof(float), &cNormal[0]);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
  glBufferData(GL_ARRAY_BUFFER, cTexture.size() * sizeof(float), 0, GL_DYNAMIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, cTexture.size() * sizeof(float), &cTexture[0]);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glCheckError(UTILS_DEBUG_LINE); // This is to eventually catch errors
}

void cubeBox::buildGeometry(){
  cubeSystem* CS=cubeSystem::getCubeSystem();
  cVertex.clear();
  cNormal.clear();
  cTexture.clear();
  for (set<cube>::iterator i=cubes.begin(); i!=cubes.end(); i++){
    cube left((*i).x-1, (*i).y, (*i).z);
    cube right((*i).x+1, (*i).y, (*i).z);
    cube down((*i).x, (*i).y-1, (*i).z);
    cube up((*i).x, (*i).y+1, (*i).z);
    cube _far((*i).x, (*i).y, (*i).z-1);
    cube _near((*i).x, (*i).y, (*i).z+1);
    /*for (int j=0; j<6; j++){
      for (int k=0; k<4; k++){
        cVertex.push_back(vertex[j*3+0]+1*(*i).x);
        cVertex.push_back(vertex[j*3+1]+1*(*i).y);
        cVertex.push_back(vertex[j*3+2]+1*(*i).z);

        cNormal.push_back(normal[j*3+0]);
        cNormal.push_back(normal[j*3+1]);
        cNormal.push_back(normal[j*3+2]);

        cTexture.push_back(texture[j*2+0]);
        cTexture.push_back(texture[j*2+1]);
      }
    }*/
    /*for (int j=0; j<24; j++){
      cVertex.push_back(vertex[j*3+0]+1*(*i).x);
      cVertex.push_back(vertex[j*3+1]+1*(*i).y);
      cVertex.push_back(vertex[j*3+2]+1*(*i).z);

      cNormal.push_back(normal[j*3+0]);
      cNormal.push_back(normal[j*3+1]);
      cNormal.push_back(normal[j*3+2]);

      cTexture.push_back(texture[j*2+0]);
      cTexture.push_back(texture[j*2+1]);
    }*/
    //if (cubes.find(down)==cubes.end())
    if (!CS->find((*i).x, (*i).y-1, (*i).z))
      for (int j=0; j<4; j++){
        cVertex.push_back(vertex[j*3+0]+1*(*i).x);
        cVertex.push_back(vertex[j*3+1]+1*(*i).y);
        cVertex.push_back(vertex[j*3+2]+1*(*i).z);

        cNormal.push_back(normal[j*3+0]);
        cNormal.push_back(normal[j*3+1]);
        cNormal.push_back(normal[j*3+2]);

        switch ((*i).type){
          case 0:
            cTexture.push_back(texture2[j*2+0]);
            cTexture.push_back(texture2[j*2+1]);
            break;
          case 1:
            cTexture.push_back(texture[j*2+0]);
            cTexture.push_back(texture[j*2+1]);
            break;
          case 2:
            cTexture.push_back(texture3[j*2+0]);
            cTexture.push_back(texture3[j*2+1]);
            break;
          case 3:
            cTexture.push_back(tnt3[j*2+0]);
            cTexture.push_back(tnt3[j*2+1]);
            break;
          case 4:
            cTexture.push_back(tronco4[j*2+0]);
            cTexture.push_back(tronco4[j*2+1]);
            break;
          case 5:
            cTexture.push_back(sand5[j*2+0]);
            cTexture.push_back(sand5[j*2+1]);
            break;
        }
      }
    //if (cubes.find(up)==cubes.end())
    if (!CS->find((*i).x, (*i).y+1, (*i).z))
      for (int j=4; j<8; j++){
        cVertex.push_back(vertex[j*3+0]+1*(*i).x);
        cVertex.push_back(vertex[j*3+1]+1*(*i).y);
        cVertex.push_back(vertex[j*3+2]+1*(*i).z);

        cNormal.push_back(normal[j*3+0]);
        cNormal.push_back(normal[j*3+1]);
        cNormal.push_back(normal[j*3+2]);

        switch ((*i).type){
          case 0:
            cTexture.push_back(texture2[j*2+0]);
            cTexture.push_back(texture2[j*2+1]);
            break;
          case 1:
            cTexture.push_back(texture[j*2+0]);
            cTexture.push_back(texture[j*2+1]);
            break;
          case 2:
            cTexture.push_back(texture3[j*2+0]);
            cTexture.push_back(texture3[j*2+1]);
            break;
          case 3:
            cTexture.push_back(tnt3[j*2+0]);
            cTexture.push_back(tnt3[j*2+1]);
            break;
          case 4:
            cTexture.push_back(tronco4[j*2+0]);
            cTexture.push_back(tronco4[j*2+1]);
            break;
          case 5:
            cTexture.push_back(sand5[j*2+0]);
            cTexture.push_back(sand5[j*2+1]);
            break;
        }
      }
    //if (cubes.find(_far)==cubes.end())
    if (!CS->find((*i).x, (*i).y, (*i).z-1))
      for (int j=8; j<12; j++){
        cVertex.push_back(vertex[j*3+0]+1*(*i).x);
        cVertex.push_back(vertex[j*3+1]+1*(*i).y);
        cVertex.push_back(vertex[j*3+2]+1*(*i).z);

        cNormal.push_back(normal[j*3+0]);
        cNormal.push_back(normal[j*3+1]);
        cNormal.push_back(normal[j*3+2]);

        switch ((*i).type){
          case 0:
            cTexture.push_back(texture2[j*2+0]);
            cTexture.push_back(texture2[j*2+1]);
            break;
          case 1:
            cTexture.push_back(texture[j*2+0]);
            cTexture.push_back(texture[j*2+1]);
            break;
          case 2:
            cTexture.push_back(texture3[j*2+0]);
            cTexture.push_back(texture3[j*2+1]);
            break;
          case 3:
            cTexture.push_back(tnt3[j*2+0]);
            cTexture.push_back(tnt3[j*2+1]);
            break;
          case 4:
            cTexture.push_back(tronco4[j*2+0]);
            cTexture.push_back(tronco4[j*2+1]);
            break;
          case 5:
            cTexture.push_back(sand5[j*2+0]);
            cTexture.push_back(sand5[j*2+1]);
            break;
        }
      }
    //if (cubes.find(_near)==cubes.end())
    if (!CS->find((*i).x, (*i).y, (*i).z+1))
      for (int j=12; j<16; j++){
        cVertex.push_back(vertex[j*3+0]+1*(*i).x);
        cVertex.push_back(vertex[j*3+1]+1*(*i).y);
        cVertex.push_back(vertex[j*3+2]+1*(*i).z);

        cNormal.push_back(normal[j*3+0]);
        cNormal.push_back(normal[j*3+1]);
        cNormal.push_back(normal[j*3+2]);

        switch ((*i).type){
          case 0:
            cTexture.push_back(texture2[j*2+0]);
            cTexture.push_back(texture2[j*2+1]);
            break;
          case 1:
            cTexture.push_back(texture[j*2+0]);
            cTexture.push_back(texture[j*2+1]);
            break;
          case 2:
            cTexture.push_back(texture3[j*2+0]);
            cTexture.push_back(texture3[j*2+1]);
            break;
          case 3:
            cTexture.push_back(tnt3[j*2+0]);
            cTexture.push_back(tnt3[j*2+1]);
            break;
          case 4:
            cTexture.push_back(tronco4[j*2+0]);
            cTexture.push_back(tronco4[j*2+1]);
            break;
          case 5:
            cTexture.push_back(sand5[j*2+0]);
            cTexture.push_back(sand5[j*2+1]);
            break;
        }
      }
    //if (cubes.find(left)==cubes.end())
    if (!CS->find((*i).x-1, (*i).y, (*i).z))
      for (int j=16; j<20; j++){
        cVertex.push_back(vertex[j*3+0]+1*(*i).x);
        cVertex.push_back(vertex[j*3+1]+1*(*i).y);
        cVertex.push_back(vertex[j*3+2]+1*(*i).z);

        cNormal.push_back(normal[j*3+0]);
        cNormal.push_back(normal[j*3+1]);
        cNormal.push_back(normal[j*3+2]);

        switch ((*i).type){
          case 0:
            cTexture.push_back(texture2[j*2+0]);
            cTexture.push_back(texture2[j*2+1]);
            break;
          case 1:
            cTexture.push_back(texture[j*2+0]);
            cTexture.push_back(texture[j*2+1]);
            break;
          case 2:
            cTexture.push_back(texture3[j*2+0]);
            cTexture.push_back(texture3[j*2+1]);
            break;
          case 3:
            cTexture.push_back(tnt3[j*2+0]);
            cTexture.push_back(tnt3[j*2+1]);
            break;
          case 4:
            cTexture.push_back(tronco4[j*2+0]);
            cTexture.push_back(tronco4[j*2+1]);
            break;
          case 5:
            cTexture.push_back(sand5[j*2+0]);
            cTexture.push_back(sand5[j*2+1]);
            break;
        }
      }
    //if (cubes.find(right)==cubes.end())
    if (!CS->find((*i).x+1, (*i).y, (*i).z))
      for (int j=20; j<24; j++){
        cVertex.push_back(vertex[j*3+0]+1*(*i).x);
        cVertex.push_back(vertex[j*3+1]+1*(*i).y);
        cVertex.push_back(vertex[j*3+2]+1*(*i).z);

        cNormal.push_back(normal[j*3+0]);
        cNormal.push_back(normal[j*3+1]);
        cNormal.push_back(normal[j*3+2]);

        switch ((*i).type){
          case 0:
            cTexture.push_back(texture2[j*2+0]);
            cTexture.push_back(texture2[j*2+1]);
            break;
          case 1:
            cTexture.push_back(texture[j*2+0]);
            cTexture.push_back(texture[j*2+1]);
            break;
          case 2:
            cTexture.push_back(texture3[j*2+0]);
            cTexture.push_back(texture3[j*2+1]);
            break;
          case 3:
            cTexture.push_back(tnt3[j*2+0]);
            cTexture.push_back(tnt3[j*2+1]);
            break;
          case 4:
            cTexture.push_back(tronco4[j*2+0]);
            cTexture.push_back(tronco4[j*2+1]);
            break;
          case 5:
            cTexture.push_back(sand5[j*2+0]);
            cTexture.push_back(sand5[j*2+1]);
            break;
        }
    }
  }

  copyData();
}
