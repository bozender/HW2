@echo off
g++ -c *.cpp -std=c++17 -Os
g++ *.o -g -o app
del /f *.o
PAUSE