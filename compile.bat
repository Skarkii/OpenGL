@ECHO OFF
cd ./src
cmake -S . -B ../Build -G "MinGW Makefiles" 
cd ../Build 
mingw32-make.exe 