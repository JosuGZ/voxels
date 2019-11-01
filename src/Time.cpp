#include "Time.h"

#include <chrono>

using namespace std::chrono;

high_resolution_clock::time_point t1, tStart, t2;
double tFrames=0, tTotal=0;

void start(void) {
  t1 = high_resolution_clock::now();
  tStart = t1;
}

void update(void) {
  t2 = high_resolution_clock::now();
  tFrames = duration_cast<duration<double>>(t2 - t1).count();
  tTotal = duration_cast<duration<double>>(t2 - tStart).count();
  t1 = high_resolution_clock::now();
}

double getTotalTime() {
  return tTotal;
}

double getLastTime() {
  return tFrames;
}
