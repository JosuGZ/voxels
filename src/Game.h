#ifndef GAME_H
#define GAME_H

#include "cube.h"

class cubeSystem;

class Game {
public:
  bool Teclas[256]; // TODO: Make private

//float px=0,py=0,pz=0, angle=0;
float px=1, py=10, pz=1; // TODO: Player position?
float vx=0, vy=0, vz=0;  // TODO: View position?
float angleX=0;//3.14/2;
float angleY=0;

float vY=0; // TODO: ????

  Game();
  void init();
  void selectNextCube();
  void update();
  void render();

private:
  cubeSystem* mCubeSystem = nullptr;
  int mTypeCubeSelected = 2;
  cube mSelectedCube;
  int mSelectedFace;
};

#endif // GAME_H
