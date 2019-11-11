#include "Game.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <gl/gl.h>
#include <gl/glu.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "graphics/graphic_functions.h"
#include "Time.h"
#include "CubeSystem.hpp"

// TODO: Refactor!
class point {
public:
  float x, y, z;
  float px, py, pz;
  char axis;
  point(float x, float y, float z, char a):x(x), y(y), z(z), axis(a) {
    //cout << x << ", " << y << " ," << z << endl;
  }
  void setCrap(float apx, float apy, float apz) {
    px = apx;
    py = apy;
    pz = apz;
  }
  bool operator<(const point& p) const {
    return pow(x-px,2)+pow(y-py,2)+pow(z-pz,2) < pow(p.x-px,2)+pow(p.y-py,2)+pow(p.z-pz,2);
  }
};

//Texturas
GLuint cesped;
void cargaTexturas(void) {
  int width, height, bpp;
  uint8_t* rgb_image = stbi_load("tMinecraft.bmp", &width, &height, &bpp, 3);

  stbi_image_free(rgb_image);
  glGenTextures(1, &cesped);
  glBindTexture(GL_TEXTURE_2D, cesped);

  gluBuild2DMipmaps(
    GL_TEXTURE_2D, 4, width,
    height, GL_RGB,
    GL_UNSIGNED_BYTE, rgb_image
  );

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, cesped);
}

Game::Game() {}

void Game::init() {
  mCubeSystem = cubeSystem::initCubeSystem();

  start();
  cargaTexturas();
  for (int x = -100; x <= 100; ++x) {
    for (int z = -100; z <= 100; ++z) {
      int height = 60 + 5 * sin((double)x/100) + 5 * cos((double)z/100);
      height += 5 * sin((double)x/20) + 5 * cos((double)z/20);
      height +=  + 5 * sin((double)x/10) + 5 * cos((double)z/10);
      for (int y = 0; y <= height; ++y) {
        mCubeSystem->addCube(x,y,z);
      }
    }
  }
}

void Game::moveCursor(double x, double y) {
  angleY=fmod((angleY+y*getLastTime()),2*M_PI);
  angleX+=x*getLastTime();
}

void Game::selectPreviousCube() {
  --mTypeCubeSelected;
  if (mTypeCubeSelected < 0) mTypeCubeSelected = 5;
}

void Game::selectNextCube() {
  mTypeCubeSelected = (mTypeCubeSelected + 1) % 6;
}

void Game::update() {
  #define VMOV 5 // TODO: Change
  #define PJUMP 5 // TODO: Change

  // Movement
  float pxTemp=px, pzTemp=pz;
  if (Teclas[(int)0x57]) {
    pxTemp+=sin(angleX)*VMOV*getLastTime();
    pzTemp-=cos(angleX)*VMOV*getLastTime();
    /*if(!CS->collision(pxTemp-0.5, pxTemp+0.5,
              py, py+1.7,
              pzTemp-0.5, pzTemp+0.5 )){
      px=pxTemp;
      pz=pzTemp;
    }*/
  }
  if (Teclas[(int)0x53]) {
    pxTemp-=sin(angleX)*VMOV*getLastTime();
    pzTemp+=cos(angleX)*VMOV*getLastTime();
    /*if(!CS->collision(pxTemp-0.5, pxTemp+0.5,
              py, py+1.7,
              pzTemp-0.5, pzTemp+0.5 )){
      px=pxTemp;
      pz=pzTemp;
    }*/
  }
  if (Teclas[(int)0x41]) {
    pzTemp-=sin(angleX)*VMOV*getLastTime();
    pxTemp-=cos(angleX)*VMOV*getLastTime();
    /*if(!CS->collision(pxTemp-0.5, pxTemp+0.5,
              py, py+1.7,
              pzTemp-0.5, pzTemp+0.5 )){
      px=pxTemp;
      pz=pzTemp;
    }*/
  }
  if (Teclas[(int)0x44]) {
    pzTemp+=sin(angleX)*VMOV*getLastTime();
    pxTemp+=cos(angleX)*VMOV*getLastTime();
    /*if(!CS->collision(pxTemp-0.5, pxTemp+0.5,
              py, py+1.7,
              pzTemp-0.5, pzTemp+0.5 )){
      px=pxTemp;
      pz=pzTemp;
    }*/
  }
  if (!mCubeSystem->collision(
    pxTemp-0.3, pxTemp+0.3,
    py, py+1.7,
    pzTemp-0.3, pzTemp+0.3)
  ) {
    px=pxTemp;
    pz=pzTemp;
  }

  float pyTemp=py+vY*getLastTime();
  if (!mCubeSystem->collision(
    px-0.3, px+0.3,
    pyTemp, pyTemp+1.7,
    pz-0.3, pz+0.3)
  ) {
    vY-=9.8*getLastTime();
    py=pyTemp;
  } else {
    vY=0;
  }
  if (py < -10000) py = 10000;

  // Move cursor
  // TODO: Don't use keys and curor
  double mouseX = 0, mouseY = 0;
  if (Teclas[VK_UP]) {
    mouseY -= 2;
  }
  if (Teclas[VK_DOWN]) {
    mouseY += 2;
  }
  if (Teclas[VK_LEFT]) {
    mouseX -= 2;
  }
  if (Teclas[VK_RIGHT]) {
    mouseX += 2;
  }
  moveCursor(mouseX, mouseY);

  // Jump code
  static bool spacePressed;
  if (Teclas[VK_SPACE] && !spacePressed && !vY) {
    spacePressed=true;
    vY=PJUMP;
  }
  else if (!Teclas[VK_SPACE])
    spacePressed=false;

  //vx-=9.8*getLastTime();
  px+=vx;

  static float h, hp, x, y, a1, a2; // TODD: Review this (a1, a2)
  h=sin(angleY);
  hp=cos(angleY);

  x=hp*cos(angleX);
  y=hp*sin(angleX);

  if(x!=0)
    a1=atan(h/x);
  else if(x>0)
    a1=M_PI;
  else
    a1=-M_PI;

  if(y!=0)
    a2=atan(h/y);
  else if(y>0)
    a2=-M_PI;
  else
    a2=M_PI;

  /*if(angleX>M_PI*2)
    angleX-=M_PI*2;
  if(angleX<0)
    angleX+=M_PI*2;
  if(angleY>M_PI*2)
    angleY-=M_PI*2;
  if(angleY<0)
    angleY+=M_PI*2;*/
  //static float ux, uy;

  // Check if we have to add or remove a cube
  static bool enterPressed;
  static bool addCube=false;
  if (Teclas[VK_RETURN] && !enterPressed) {
    enterPressed=true;
    //CS->addCube(floor(px),floor(py),floor(pz));
    addCube=true;
    //py+=1;
  }
  else if (!Teclas[VK_RETURN]) {
    enterPressed=false;
    addCube=false;
  }
  static bool ePressed;
  static bool removeCube=false;
  if (Teclas[0x45] && !ePressed) {
    ePressed=true;
    //CS->addCube(floor(px),floor(py),floor(pz));
    removeCube=true;
    //cout << "hei";
    //py+=1;
  } else if (!Teclas[0x45]){
    ePressed=false;
    removeCube=false;
  }

      //Código para encontrar el cubo seleccionado
      mSelectedFace = -1;
      vector<point> pointsToCheck;
      for (auto &p: pointsToCheck) {
        p.setCrap(px, py, pz); // TODO: This is ugly
      }
      float vcx=-1*cos(angleY)*sin(angleX), vcy=1*sin(angleY), vcz=1*cos(angleY)*cos(angleX);
      float t;
      for (int i=((int) px)-5; i<=((int) px)+5; i++) {
        if (vcx) {
          t=(i-px)/vcx;
          point p(px+vcx*t, py+1.7+vcy*t, pz+vcz*t, 'x');
          p.setCrap(px, py, pz); // TODO: This is ugly
          if (t<0) pointsToCheck.push_back(p);
        }
      }
      for (int i=((int) (py+1.7))-5; i<=((int) (py+1.7))+5; i++) {
        if (vcy) {
          t=(i-py-1.7)/vcy;
          point p(px+vcx*t, py+1.7+vcy*t, pz+vcz*t, 'y');
          p.setCrap(px, py, pz); // TODO: This is ugly
          if (t<0) pointsToCheck.push_back(p);
        }
      }
      for (int i=((int) pz)-5; i<=((int) pz)+5; i++) {
        if (vcz) {
          t=(i-pz)/vcz;
          point p(px+vcx*t, py+1.7+vcy*t, pz+vcz*t, 'z');
          p.setCrap(px, py, pz); // TODO: This is ugly
          if (t<0) pointsToCheck.push_back(p);
        }
      }
      sort(pointsToCheck.begin(), pointsToCheck.end());
      bool b=false;
      for (auto i = pointsToCheck.begin(); i!=pointsToCheck.end() && !b; i++) {
        const cube *c1=NULL;
        const cube *c2=NULL;
        switch (i->axis) {
          case 'x':
            c1 = mCubeSystem->find(floor(i->x-0.5),floor(i->y),floor(i->z));
            c2 = mCubeSystem->find(floor(i->x+0.5),floor(i->y),floor(i->z));
            if (!c2 && c1) {
              { mSelectedCube = *c1; mSelectedFace = 5; b = true; }
              if(addCube) {
                mCubeSystem->addCube(floor(i->x+0.5),floor(i->y),floor(i->z),mTypeCubeSelected);
                addCube=false;
              }
              if(removeCube) {
                mCubeSystem->removeCube(floor(i->x-0.5),floor(i->y),floor(i->z));
                removeCube=false;
              }
            }
            if (!c1 && c2) {
              { mSelectedCube = *c2; mSelectedFace = 4; b = true; }
              if(addCube) {
                mCubeSystem->addCube(floor(i->x-0.5),floor(i->y),floor(i->z),mTypeCubeSelected);
                addCube=false;
              }
              if(removeCube) {
                mCubeSystem->removeCube(floor(i->x+0.5),floor(i->y),floor(i->z));
                removeCube=false;
              }
            }
            break;
          case 'y':
            c1 = mCubeSystem->find(floor(i->x),floor(i->y-0.5),floor(i->z));
            c2 = mCubeSystem->find(floor(i->x),floor(i->y+0.5),floor(i->z));
            if (!c2 && c1) {
              { mSelectedCube = *c1; mSelectedFace = 1; b = true; }
              if(addCube) {
                mCubeSystem->addCube(floor(i->x),floor(i->y+0.5),floor(i->z),mTypeCubeSelected);
                addCube=false;
              }
              if(removeCube) {
                mCubeSystem->removeCube(floor(i->x),floor(i->y-0.5),floor(i->z));
                removeCube=false;
              }
            }
            if (!c1 && c2) {
              { mSelectedCube = *c2; mSelectedFace = 0; b = true; }
              if(addCube) {
                mCubeSystem->addCube(floor(i->x),floor(i->y-0.5),floor(i->z),mTypeCubeSelected);
                addCube=false;
              }
              if(removeCube) {
                mCubeSystem->removeCube(floor(i->x),floor(i->y+0.5),floor(i->z));
                removeCube=false;
              }
            }
            break;
          case 'z':
            c1 = mCubeSystem->find(floor(i->x),floor(i->y),floor(i->z-0.5));
            c2 = mCubeSystem->find(floor(i->x),floor(i->y),floor(i->z+0.5));
            if (!c2 && c1) {
              { mSelectedCube = *c1; mSelectedFace = 3; b = true; }
              if(addCube) {
                mCubeSystem->addCube(floor(i->x),floor(i->y),floor(i->z+0.5),mTypeCubeSelected);
                addCube=false;
              }
              if(removeCube) {
                mCubeSystem->removeCube(floor(i->x),floor(i->y),floor(i->z-0.5));
                removeCube=false;
              }
            }
            if (!c1 && c2) {
              { mSelectedCube = *c2; mSelectedFace = 2; b = true; }
              if(addCube) {
                mCubeSystem->addCube(floor(i->x),floor(i->y),floor(i->z-0.5),mTypeCubeSelected);
                addCube=false;
              }
              if(removeCube) {
                mCubeSystem->removeCube(floor(i->x),floor(i->y),floor(i->z+0.5));
                removeCube=false;
              }
            }
            break;
        }
        /*if (!c2 && c1) {c1->selFace(5);break;}
        if (!c1 && c2) {c2->selFace(4);break;}*/
      }
      //drawFace(0);
      //drawFace(5);
}

void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 1.81, 0.1, 10000);
  //glRotatef(180,0.2,1,0.2);
  //glTranslatef(0,-5,15);

  glRotatef(180/M_PI*angleX,0,1,0);
  //glRotatef(180/M_PI*angleX,cos(angleX),sin(angleX),0);
  glRotatef(180/M_PI*angleY,cos(angleX),0,sin(angleX));
  //if(angleX<angleY)
  //glRotatef(180,angleY/M_PI,angleX/M_PI,0);
  //else
  //glRotatef(180/M_PI*angleY,1,angleX/angleY,0);
  //glRotatef(180/3.14*a2,0,0,1);
  //glRotatef(180/3.14*a1,1,0,0);
  glTranslatef(-px,-py-1.7,-pz);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  ejes();
  /*GLfloat position[] = {px, py+1.7, pz, 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, position);*/

  glPointSize(1);
  //glTranslatef(0,-5,-10);
  static int ib=0;
  ib++;
  //glRotatef(ib,1,1,1);
  glColor3f(0.5,0.5,0.5);

  /*glBegin(GL_QUADS);
    glVertex2f(-1,-1);
    glVertex2f(1,-1);
    glVertex2f(1,1);
    glVertex2f(-1,1);
  glEnd();*/

  //drawCube();
  //char title[100];
  //sprintf(title, "%f ,%f ,%f, FPS: %f, angleX: %f", px, py, pz, 1/getLastTime(), angleX); // TODO: Change title
  //SetWindowText(hWnd, title);
  mCubeSystem->drawAllCubes(px, py, pz, angleX, angleY);

      // Cubo central
      glMatrixMode(GL_MODELVIEW);
      glDisable(GL_LIGHTING);
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glLoadIdentity();
      //glTranslatef((float)px,(float)py,(float)pz);
      glColor4f(1,0,0,0.2);
      drawCube();
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_LIGHTING);

  if (mSelectedFace >= 0) {
    mSelectedCube.selFace(mSelectedFace);
  }

  cruceta();
  glPopMatrix();
}
