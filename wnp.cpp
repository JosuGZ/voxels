#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include "TimeWindows.h"
#include <Math.h>
#include "CubeSystem.hpp"
#include <stdio.h>

using namespace std;

bool Teclas[256];

//float px=0,py=0,pz=0, angle=0;
float px=1, py=10, pz=1; 
float vx=0, vy=0, vz=0; 
float angleX=0;//3.14/2;
float angleY=0;

float vY=0;

int typeCubeSelected=2;

#include "corona.h"
//Texturas
GLuint cesped;

            class point{
            public:
                float x, y, z;
                char axis;
                point(float x, float y, float z, char a):x(x), y(y), z(z), axis(a){
                    //cout << x << ", " << y << " ," << z << endl;
                }
                bool operator<(const point& p) const{
                    return pow(x-px,2)+pow(y-py,2)+pow(z-pz,2) < pow(p.x-px,2)+pow(p.y-py,2)+pow(p.z-pz,2);
                }
            };

void cargaTexturas(void)
{
  corona::Image* imagen=NULL;
  
  imagen = corona::OpenImage("tMinecraft.bmp", corona::PF_R8G8B8);
  glGenTextures(1, &cesped);
  glBindTexture(GL_TEXTURE_2D, cesped);
  //glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->getWidth(), imagen->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->getPixels());
  
  
    /*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);*/
    
        
    gluBuild2DMipmaps( GL_TEXTURE_2D, 4, imagen->getWidth(), 
           imagen->getHeight() , GL_RGB, 
           GL_UNSIGNED_BYTE, imagen->getPixels() );

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,
                GL_NEAREST );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,
                GL_NEAREST );

    glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, cesped);
}

void ejes()
{
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

/*void cruceta()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0,rect.right,rect.bottom,0,-1,1);
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    
    glLineWidth(3);
    glColor4f(0,1,0,0.5);
    glBegin(GL_LINES);
        glVertex3f(rect.right/2+15,rect.bottom/2,0);
        glVertex3f(rect.right/2+35,rect.bottom/2,0);
        
        glVertex3f(rect.right/2+-15,rect.bottom/2,0);
        glVertex3f(rect.right/2-35,rect.bottom/2,0);
        
        glVertex3f(rect.right/2,rect.bottom/2+15,0);
        glVertex3f(rect.right/2,rect.bottom/2+35,0);
        
        glVertex3f(rect.right/2,rect.bottom/2-15,0);
        glVertex3f(rect.right/2,rect.bottom/2-35,0);
    glEnd();
    
    glEnable(GL_DEPTH_TEST);
    light::restore();
}*/void cruceta()
{
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

    //glScalef(100,100,100);
    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.81, 0.1, 10000);
    glOrtho(-1,1,-1,1,-1,1);*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.81, 0.1, 10000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4f(1,1,1,0.5);
    //glTranslatef(-1,-1,0);
    glScalef(0.5,0.5,0.5);
    drawMiniCube(typeCubeSelected);

    /*glBegin(GL_QUADS);
        glVertex3f(0, 100, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(100, 0, 0);
        glVertex3f(100, 100, 0);
    glEnd();*/
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    //light::restore();
}

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam);

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /*glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);*/

    /* create and enable the render context (RC) */
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

cubeSystem* CS=NULL;

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
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
        10, 10, 1000, 550, NULL, NULL, hInstance, NULL);

    EnableOpenGL(hWnd, &hDC, &hRC);

    CS = cubeSystem::initCubeSystem();
	//CS->addCube(0,0,0);
	//CS->addCube(-1,0,0);
	//CS->addCube(px,0,py);
	//CS->addCube(-1,0,1);
	//CS->addCube(0,0,1);
	//CS->addCube(0,1,0);
	//CS->addCube(-10,1,0);
	#define RANDOM_CUBES 00000
	start();
    int i;
	for(i=0; i<RANDOM_CUBES; i++)
	{
		CS->addCube(rand()%400-200,rand()%400-200,rand()%400-200,rand()%6);
		if(i%1000==0){
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
		CS->addCube(0,1,0);
        CS->addCube(1,1,0);
        CS->addCube(2,1,0);
        CS->addCube(3,1,0);
        CS->addCube(4,1,0);
        CS->addCube(5,1,0);
        CS->addCube(1,2,0);
        CS->addCube(2,2,0);
        CS->addCube(3,2,0);
        CS->addCube(4,2,0);
        CS->addCube(5,2,0);
        CS->addCube(2,3,0);
        CS->addCube(3,3,0);
        CS->addCube(4,3,0);
        CS->addCube(5,3,0);
        CS->addCube(3,4,0);
        CS->addCube(4,4,0);
        CS->addCube(5,4,0);
        CS->addCube(4,5,0);
        CS->addCube(5,5,0);
        CS->addCube(5,6,0);
        CS->addCube(5,1,5);
        CS->addCube(2,1,0);
    cargaTexturas();
    for (int camb=-100; camb<=0; camb++)
        for (i=-100; i<100; i++)
            for (int j=-100; j<100; j++)
                CS->addCube(i,camb,j);
	start();
	
    update();
    while (true)
    {
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                break;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
			update();
			//px=cos(angleX)*dist;
			//py=sin(angleX)*dist;
			//angleX+=0.005;
            #define VMOV 5
            #define PJUMP 5
            float pxTemp=px, pzTemp=pz;
			if (Teclas[(int)0x57])
			{
                pxTemp+=sin(angleX)*VMOV*getLastTime();
                pzTemp-=cos(angleX)*VMOV*getLastTime();
                /*if(!CS->collision(pxTemp-0.5, pxTemp+0.5,
                                  py, py+1.7,
                                  pzTemp-0.5, pzTemp+0.5 )){
				    px=pxTemp;
				    pz=pzTemp;
                }*/
			}
			if (Teclas[(int)0x53])
			{
                pxTemp-=sin(angleX)*VMOV*getLastTime();
                pzTemp+=cos(angleX)*VMOV*getLastTime();
                /*if(!CS->collision(pxTemp-0.5, pxTemp+0.5,
                                  py, py+1.7,
                                  pzTemp-0.5, pzTemp+0.5 )){
                    px=pxTemp;
                    pz=pzTemp;
                }*/
			}
			if (Teclas[(int)0x41])
			{
                pzTemp-=sin(angleX)*VMOV*getLastTime();
                pxTemp-=cos(angleX)*VMOV*getLastTime();
                /*if(!CS->collision(pxTemp-0.5, pxTemp+0.5,
                                  py, py+1.7,
                                  pzTemp-0.5, pzTemp+0.5 )){
                    px=pxTemp;
                    pz=pzTemp;
                }*/
			}
			if (Teclas[(int)0x44])
			{
                pzTemp+=sin(angleX)*VMOV*getLastTime();
                pxTemp+=cos(angleX)*VMOV*getLastTime();
                /*if(!CS->collision(pxTemp-0.5, pxTemp+0.5,
                                  py, py+1.7,
                                  pzTemp-0.5, pzTemp+0.5 )){
                    px=pxTemp;
                    pz=pzTemp;
                }*/
			}
            if(!CS->collision(pxTemp-0.3, pxTemp+0.3,
                                  py, py+1.7,
                                  pzTemp-0.3, pzTemp+0.3 )){
                    px=pxTemp;
                    pz=pzTemp;
            }
			if (Teclas[VK_UP])
			{
				angleY=fmod((angleY-2*getLastTime()),2*M_PI);
				//py+=10*getLastTime();
			}
			if (Teclas[VK_DOWN])
			{
				angleY=fmod((angleY+2*getLastTime()),2*M_PI);
				//py-=10*getLastTime();
			}
			/*if (Teclas[VK_SPACE])
			{//CS->addCube(-(int)px,(int)py,-(int)pz);
				//py+=10*getLastTime();
                vY=PJUMP;
			}*/
            static bool spacePressed;
            if (Teclas[VK_SPACE] && !spacePressed && !vY)
            {
                spacePressed=true;
                vY=PJUMP;
            }
            else if (!Teclas[VK_SPACE])
                spacePressed=false;
			/*if (Teclas[0x43])//C
			{
				py-=10*getLastTime();
			}*/
			if (Teclas[VK_LEFT])
			{
				angleX-=2*getLastTime();
			}
			if (Teclas[VK_RIGHT])
			{
				angleX+=2*getLastTime();
			}
            static bool enterPressed;
            static bool addCube=false;
            if (Teclas[VK_RETURN] && !enterPressed)
            {
                enterPressed=true;
                //CS->addCube(floor(px),floor(py),floor(pz));
                addCube=true;
                //py+=1;
            }
            else if (!Teclas[VK_RETURN]){
                enterPressed=false;
                addCube=false;
            }
            static bool ePressed;
            static bool removeCube=false;
            if (Teclas[0x45] && !ePressed)
            {
                ePressed=true;
                //CS->addCube(floor(px),floor(py),floor(pz));
                removeCube=true;
                //cout << "hei";
                //py+=1;
            }
            else if (!Teclas[0x45]){
                ePressed=false;
                removeCube=false;
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glPushMatrix();
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60, 1.81, 0.1, 10000);
            //glRotatef(180,0.2,1,0.2);
            //glTranslatef(0,-5,15);
            
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
            sprintf(title, "%f ,%f ,%f, FPS: %f, angleX: %f", px, py, pz, 1/getLastTime(), angleX);
            SetWindowText(hWnd, title);
            CS->drawAllCubes(px, py, pz, angleX, angleY);

            //Código para encontrar el cubo seleccionado
            vector<point> pointsToCheck;
            float vcx=-1*cos(angleY)*sin(angleX), vcy=1*sin(angleY), vcz=1*cos(angleY)*cos(angleX);
            float t;
            for (i=((int) px)-5; i<=((int) px)+5; i++){
                if (vcx){
                    t=(i-px)/vcx;
                    point p(px+vcx*t, py+1.7+vcy*t, pz+vcz*t, 'x');
                    if (t<0) pointsToCheck.push_back(p);
                }
            }
            for (i=((int) (py+1.7))-5; i<=((int) (py+1.7))+5; i++){
                if (vcy){
                    t=(i-py-1.7)/vcy;
                    point p(px+vcx*t, py+1.7+vcy*t, pz+vcz*t, 'y');
                    if (t<0) pointsToCheck.push_back(p);
                }
            }
            for (i=((int) pz)-5; i<=((int) pz)+5; i++){
                if (vcz){
                    t=(i-pz)/vcz;
                    point p(px+vcx*t, py+1.7+vcy*t, pz+vcz*t, 'z');
                    if (t<0) pointsToCheck.push_back(p);
                }
            }
            sort(pointsToCheck.begin(), pointsToCheck.end());
            vector<point>::iterator i=pointsToCheck.begin();
            bool b=false;
            for (i; i!=pointsToCheck.end() && !b; i++){
                const cube *c1=NULL;
                const cube *c2=NULL;
                switch (i->axis){
                    case 'x':
                        c1 = CS->find(floor(i->x-0.5),floor(i->y),floor(i->z));
                        c2 = CS->find(floor(i->x+0.5),floor(i->y),floor(i->z));
                        if (!c2 && c1) {c1->selFace(5);b=true;
                            if(addCube){
                                CS->addCube(floor(i->x+0.5),floor(i->y),floor(i->z),typeCubeSelected);
                                addCube=false;
                            }
                            if(removeCube){
                                CS->removeCube(floor(i->x-0.5),floor(i->y),floor(i->z));
                                removeCube=false;
                            }
                        }
                        if (!c1 && c2) {c2->selFace(4);b=true;
                            if(addCube){
                                CS->addCube(floor(i->x-0.5),floor(i->y),floor(i->z),typeCubeSelected);
                                addCube=false;
                            }
                            if(removeCube){
                                CS->removeCube(floor(i->x+0.5),floor(i->y),floor(i->z));
                                removeCube=false;
                            }
                        }
                        break;
                    case 'y':
                        c1 = CS->find(floor(i->x),floor(i->y-0.5),floor(i->z));
                        c2 = CS->find(floor(i->x),floor(i->y+0.5),floor(i->z));
                        if (!c2 && c1) {c1->selFace(1);b=true;
                            if(addCube){
                                CS->addCube(floor(i->x),floor(i->y+0.5),floor(i->z),typeCubeSelected);
                                addCube=false;
                            }
                            if(removeCube){
                                CS->removeCube(floor(i->x),floor(i->y-0.5),floor(i->z));
                                removeCube=false;
                            }
                        }
                        if (!c1 && c2) {c2->selFace(0);b=true;
                            if(addCube){
                                CS->addCube(floor(i->x),floor(i->y-0.5),floor(i->z),typeCubeSelected);
                                addCube=false;
                            }
                            if(removeCube){
                                CS->removeCube(floor(i->x),floor(i->y+0.5),floor(i->z));
                                removeCube=false;
                            }
                        }
                        break;
                    case 'z':
                        c1 = CS->find(floor(i->x),floor(i->y),floor(i->z-0.5));
                        c2 = CS->find(floor(i->x),floor(i->y),floor(i->z+0.5));
                        if (!c2 && c1) {c1->selFace(3);b=true;
                            if(addCube){
                                CS->addCube(floor(i->x),floor(i->y),floor(i->z+0.5),typeCubeSelected);
                                addCube=false;
                            }
                            if(removeCube){
                                CS->removeCube(floor(i->x),floor(i->y),floor(i->z-0.5));
                                removeCube=false;
                            }
                        }
                        if (!c1 && c2) {c2->selFace(2);b=true;
                            if(addCube){
                                CS->addCube(floor(i->x),floor(i->y),floor(i->z-0.5),typeCubeSelected);
                                addCube=false;
                            }
                            if(removeCube){
                                CS->removeCube(floor(i->x),floor(i->y),floor(i->z+0.5));
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
            ////////////////////////////////////////////

            float pyTemp=py+vY*getLastTime();
            if (!CS->collision(px-0.3, px+0.3,
                               pyTemp, pyTemp+1.7,
                               pz-0.3, pz+0.3) ){
                vY-=9.8*getLastTime();
                py=pyTemp;
            }
            else
                vY=0;
            //if (CS->collision(px, py, pz)) cout << "+";
            //if (CS->collision(px, py, pz)) cout << "-";
            //if (CS->collision(px, py, pz)) cout << "=";
            
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

            cruceta();

            glPopMatrix();
            SwapBuffers(hDC);
        }
    }

    cout << lpCmdLine;
    return 0;
}

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            return 0;
        case WM_CLOSE:
            PostQuitMessage (0);
            return 0;
        case WM_DESTROY:
            return 0;
        case WM_KEYDOWN:
			Teclas[(int)wParam]=true;
			//Teclas[(int)wParam]=true;	
			switch(wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_CLOSE, 0, 0);
					break;
                case 0x43:
                    typeCubeSelected = ++typeCubeSelected%6;
                    break;
				//case VK_SPACE:
					//box* b=new box((int)-px,(int)py,(int)-pz);
					/*if (Teclas[VK_SPACE]) //Temporal, para añadir cajas
						box* b=new box(boxes[5]->px,boxes[5]->py+1,boxes[5]->pz);*/
					//break;
			} 
			break;
		case WM_KEYUP:
			Teclas[(int)wParam]=false;
			break;
            /*switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
					CS->addCube(px,py,pz);
                    return 0;
                case VK_UP:
                    py+=1;
					CS->addCube(px,py,pz);
                    return 0;
                case VK_DOWN:
                    py-=1;
					CS->addCube(px,py,pz);
                    return 0;
                case VK_LEFT:
                    px+=1;
					CS->addCube(px,py,pz);
                    return 0;
                case VK_RIGHT:
                    px-=1;
					CS->addCube(px,py,pz);
                    return 0;
                case 0x57:
                    pz+=1;
					CS->addCube(px,py,pz);
                    return 0;
                case 0x53:
                    pz-=1;
					CS->addCube(px,py,pz);
                    return 0;
            }
            return 0;*/
        default:
            return DefWindowProc (hWnd, message, wParam, lParam);
    }
}
