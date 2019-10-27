set actual=%~d0%~p0

c:\\MinGW\bin\g++ -O3 -static -o %actual%main.exe %actual%main.cpp %actual%TimeWindows.c -mwindows -mconsole -fpermissive -lopengl32 -lglu32 %actual%corona.lib -LC:\MinGW\lib

pause