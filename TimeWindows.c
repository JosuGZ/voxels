#include "TimeWindows.h"

LARGE_INTEGER t1, tInicio, t2,frecuencia;
double tFrames=0, tTotal=0;

void start(void) {
  QueryPerformanceCounter(&t1);
  tInicio=t1;
}

void update(void) {
  QueryPerformanceCounter(&t2);
  tFrames=(double)(t2.QuadPart-t1.QuadPart)/(double)frecuencia.QuadPart;
  tTotal=(double)(t2.QuadPart-tInicio.QuadPart)/(double)frecuencia.QuadPart;
  QueryPerformanceFrequency(&frecuencia);
  QueryPerformanceCounter(&t1);
}

double getTotalTime() {
  return tTotal;
}

double getLastTime() {
  return tFrames;
}
