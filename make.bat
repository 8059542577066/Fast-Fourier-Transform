@echo off
g++ complex.cpp -O3 -std=c++98 -Wall -c
pause
g++ fourier.cpp -O3 -std=c++98 -Wall -c
pause
g++ format.cpp -O3 -std=c++98 -Wall -c
pause
g++ complex.o fourier.o format.o main.cpp -O3 -std=c++98 -Wall -o run.exe
pause