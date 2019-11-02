#include "Game.h"

#include <cmath>
#include <gl/gl.h>
#include <gl/glu.h>

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
#include "corona.h"
void cargaTexturas(void) {
  corona::Image* imagen=NULL;

  imagen = corona::OpenImage("tMinecraft.bmp", corona::PF_R8G8B8);
  glGenTextures(1, &cesped);
  glBindTexture(GL_TEXTURE_2D, cesped);

  gluBuild2DMipmaps(
    GL_TEXTURE_2D, 4, imagen->getWidth(),
    imagen->getHeight() , GL_RGB,
    GL_UNSIGNED_BYTE, imagen->getPixels()
  );

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, cesped);
}

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

Game::Game() {}

void Game::init() {
  mCubeSystem = cubeSystem::initCubeSystem();

  //CS->addCube(0,0,0);
  //CS->addCube(-1,0,0);
  //CS->addCube(px,0,py);
  //CS->addCube(-1,0,1);
  //CS->addCube(0,0,1);
  //CS->addCube(0,1,0);
  //CS->addCube(-10,1,0);
  #define RANDOM_CUBES 0000000
  start();
  int i;
  for(i=0; i<RANDOM_CUBES; i++) {
    mCubeSystem->addCube(rand()%4000-2000,rand()%4000-2000,rand()%4000-2000,rand()%6);
    if(i%1000==0) {
      update();
      static double tG;
      system("cls");
      cout << "Tiempo de generación de cubo: " << tG << endl;
      cout << "Quedan " << (RANDOM_CUBES-i)*tG << " segundos" << endl;
      cout << "Completados " << i << " de " << RANDOM_CUBES << " cubos" << endl;
      static int p, q;
      p=(float)100/(float)RANDOM_CUBES*i;
      cout << "[";
      for (q=0; q<p/2; q++)
        cout << "=";
      for (; q<50; q++)
        cout << " ";
      cout << "]" << p << "\%" << endl;
      tG = getLastTime()/1000;
    }
  }
  mCubeSystem->addCube(0,1,0);
  mCubeSystem->addCube(1,1,0);
  mCubeSystem->addCube(2,1,0);
  mCubeSystem->addCube(3,1,0);
  mCubeSystem->addCube(4,1,0);
  mCubeSystem->addCube(5,1,0);
  mCubeSystem->addCube(1,2,0);
  mCubeSystem->addCube(2,2,0);
  mCubeSystem->addCube(3,2,0);
  mCubeSystem->addCube(4,2,0);
  mCubeSystem->addCube(5,2,0);
  mCubeSystem->addCube(2,3,0);
  mCubeSystem->addCube(3,3,0);
  mCubeSystem->addCube(4,3,0);
  mCubeSystem->addCube(5,3,0);
  mCubeSystem->addCube(3,4,0);
  mCubeSystem->addCube(4,4,0);
  mCubeSystem->addCube(5,4,0);
  mCubeSystem->addCube(4,5,0);
  mCubeSystem->addCube(5,5,0);
  mCubeSystem->addCube(5,6,0);
  mCubeSystem->addCube(5,1,5);
  mCubeSystem->addCube(2,1,0);
  cargaTexturas();
  for (int camb=-100; camb<=0; camb++)
    for (i=-100; i<100; i++)
      for (int j=-100; j<100; j++)
        mCubeSystem->addCube(i,camb,j);
}

void Game::selectNextCube() {
  mTypeCubeSelected = ++mTypeCubeSelected % 6;
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

  // "Mouse" up and down
  if (Teclas[VK_UP]) {
    angleY=fmod((angleY-2*getLastTime()),2*M_PI);
    //py+=10*getLastTime();
  }
  if (Teclas[VK_DOWN]) {
    angleY=fmod((angleY+2*getLastTime()),2*M_PI);
    //py-=10*getLastTime();
  }
  // Jump code
  static bool spacePressed;
  if (Teclas[VK_SPACE] && !spacePressed && !vY) {
    spacePressed=true;
    vY=PJUMP;
  }
  else if (!Teclas[VK_SPACE])
    spacePressed=false;
  // "Mouse" left and right
  if (Teclas[VK_LEFT]) {
    angleX-=2*getLastTime();
  }
  if (Teclas[VK_RIGHT]) {
    angleX+=2*getLastTime();
  }

  // Add/remove cubes here

  //vx-=9.8*getLastTime();
  px+=vx;

  static float h, hp, x, y, a1, a2;
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
      vector<point>::iterator i=pointsToCheck.begin();
      bool b=false;
      for (i; i!=pointsToCheck.end() && !b; i++) {
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
  char title[100];
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
