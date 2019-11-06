#include "graphic_functions.h"

#include <gl/gl.h>
#include <gl/glu.h>

void ejes() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);

  glLineWidth(1);
  glBegin(GL_LINES);

    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(1000,0,0);

    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,1000,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1000);

  glEnd();

  glPointSize(10);
  glBegin(GL_POINTS);
    glColor3f(1,1,0);
    glVertex3f(40,40,-30);
  glEnd();

  //glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  //light::restore();
}

void cruceta() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(0,1000,0,500,-1,1);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);

  glLineWidth(3);
  glColor4f(0,1,0,0.5);
  glBegin(GL_LINES);
    glVertex3f(1000/2+15,500/2,0);
    glVertex3f(1000/2+35,500/2,0);

    glVertex3f(1000/2+-15,500/2,0);
    glVertex3f(1000/2-35,500/2,0);

    glVertex3f(1000/2,500/2+15,0);
    glVertex3f(1000/2,500/2+35,0);

    glVertex3f(1000/2,500/2-15,0);
    glVertex3f(1000/2,500/2-35,0);
  glEnd();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 1.81, 0.1, 10000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor4f(1,1,1,0.5);
  glScalef(0.5,0.5,0.5);
  //drawMiniCube(typeCubeSelected);                                             // TODO:

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
}

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
