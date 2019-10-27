#ifndef TIME_WINDOWS
#define TIME_WINDOWS

#include <Windows.h>

void start(void);
//Deberían ser inline
void update(void);
double getTotalTime(void);
double getLastTime(void);

#endif //TIME_WINDOWS
