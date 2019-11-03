#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <Math.h>
#include <stdio.h>

#include "Time.h"
#include "Game.h"

Game game;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC) {
  PIXELFORMATDESCRIPTOR pfd;
  int iFormat;

  /* get the device context (DC) */
  *hDC = GetDC (hWnd);

  /* set the pixel format for the DC */
  ZeroMemory (&pfd, sizeof (pfd));
  pfd.nSize = sizeof (pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;
  iFormat = ChoosePixelFormat (*hDC, &pfd);
  SetPixelFormat (*hDC, iFormat, &pfd);

  *hRC = wglCreateContext( *hDC );
  wglMakeCurrent( *hDC, *hRC );

  glClearColor(0.3,0.3,1,1);

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  //glDepthFunc(GL_LEQUAL);

  //Activar iluminaciÃ³n general
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLfloat position[] = { 40, 40, -30, 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  GLfloat ambiente[] = { 1, 1, 1, 1.0 };
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);

  /*glEnable(GL_LIGHT1);
  GLfloat diffuse2[] = { 0, 0, 1, 1.0 };
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);
  GLfloat position2[] = { 4, 4, -3, 1.0 };
  glLightfv(GL_LIGHT1, GL_POSITION, position2);
  GLfloat ambiente2[] = { 0, 0, 0, 1.0 };
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente2);

  glEnable(GL_LIGHT2);
  GLfloat diffuse3[] = { 0, 1, 0, 1.0 };
  glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse3);
  GLfloat position3[] = { -4, -4, 3, 1.0 };
  glLightfv(GL_LIGHT2, GL_POSITION, position3);
  GLfloat ambiente3[] = { 0, 0, 0, 1.0 };
  glLightfv(GL_LIGHT2, GL_AMBIENT, ambiente3);*/

  glEnable (GL_LINE_SMOOTH);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
  glLineWidth(1.5);
  //glDisable(GL_DEPTH_TEST);
  glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
  //glEnable (GL_POLYGON_SMOOTH);
  glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
  //glEnable(GL_MULTISAMPLE);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_TEXTURE_2D);
}

using namespace std;

int WINAPI WinMain(
  HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/,
  LPSTR lpCmdLine, int /*iCmdShow*/
) {
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;
  HDC hDC;
  HGLRC hRC;

  wc.style = CS_OWNDC;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor (NULL, IDC_ARROW);
  wc.hbrBackground = NULL; //(HBRUSH) GetStockObject (BLACK_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "GLSample";
  RegisterClass (&wc);

  hWnd = CreateWindow (
    "GLSample", "OpenGL Sample",
    WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
    10, 10, 1000, 550, NULL, NULL, hInstance, NULL
  );

  //SetCapture(hWnd);
  ShowCursor(FALSE);

  EnableOpenGL(hWnd, &hDC, &hRC);
  game.init();

  start();

  update();
  while (true) {
    if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
      /* handle or dispatch messages */
      if (msg.message == WM_QUIT)  {
        break;
      } else {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
      }
    } else {
      update();
      game.update();
      game.render();
      SwapBuffers(hDC);
    }
  }

  cout << lpCmdLine;
  return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
  switch (message) {
    case WM_MOUSEACTIVATE:
      cout << "WM_MOUSEACTIVATE\n";
      return 0;
    //case WM_MOUSEMOVE:
    case WM_MOUSEFIRST: {
      // TODO: Review with API
      //cout << "WM_MOUSEFIRST | WM_MOUSEMOVE\n";
      double mouseX = (lParam & 0x0000FFFF) - 500;
      double mouseY = ((lParam >> 16) & 0x0000FFFF) - 275;
      tagPOINT center;
      center.x = 500;
      center.y = 275;
      game.moveCursor(mouseX / 10, mouseY / 10);
      ClientToScreen(hWnd, &center);
      SetCursorPos(center.x,center.y);
    } return 0;
    case WM_MOUSEHOVER:
      cout << "WM_MOUSEHOVER\n";
      return 0;
    case WM_MOUSELAST:
      cout << "WM_MOUSELAST\n";
      return 0;
    case WM_MOUSELEAVE:
      cout << "WM_MOUSELEAVE\n";
      return 0;
    case WM_MOUSEWHEEL: {
      cout << "WM_MOUSEWHEEL\n";
      auto delta = GET_WHEEL_DELTA_WPARAM(wParam);
      if (delta <= 0) {
        game.selectPreviousCube();
      } else {
        game.selectNextCube();
      }
      cout << "  " << (delta >= 0 ? "Up" : "Down") << "\n";
    } return 0;
    // TODO: Change this
    case WM_LBUTTONDOWN:
      game.Teclas[VK_RETURN] = true;
      return 0;
    case WM_LBUTTONUP:
      game.Teclas[VK_RETURN] = false;
      return 0;
    case WM_MBUTTONDOWN:
      cout << "WM_MBUTTONDOWN\n";
      return 0;
    case WM_MBUTTONUP:
      cout << "WM_MBUTTONUP\n";
      return 0;
    // TODO: Change this
    case WM_RBUTTONDOWN:
      game.Teclas[0x45] = true;
      return 0;
    case WM_RBUTTONUP:
      game.Teclas[0x45] = false;
      return 0;
    case WM_CREATE:
      return 0;
    case WM_CLOSE:
      PostQuitMessage (0);
      return 0;
    case WM_DESTROY:
      return 0;
    case WM_KEYDOWN:
      game.Teclas[(int)wParam] = true;
      switch(wParam)
      {
        case VK_ESCAPE:
          PostMessage(hWnd, WM_CLOSE, 0, 0);
          break;
        case 0x43:
          game.selectNextCube();
          break;
      }
      break;
    case WM_KEYUP:
      game.Teclas[(int)wParam] = false;
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}
