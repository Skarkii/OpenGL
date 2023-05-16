@echo off
echo Compiling...
set COMPILER= g++
set STANDARD= -std=c++11 -Wall
set INCLUDE= -I./include
set OUTPUT= -o ./build/main.exe
set SOURCE= ./src/main.cpp ./src/include/glad/glad.c ./src/render.cpp ./src/inputhandler.cpp ./src/vbo.cpp ./src/shader.cpp ./src/shaderProgram.cpp ./src/vao.cpp ./src/ebo.cpp ./src/texture.cpp
set LIBS= -L./src/lib
set LINK= -lglfw3 -static

%COMPILER% %STANDARD% %INCLUDE% %LIBS% %OUTPUT% %SOURCE% %LINK%
if %ERRORLEVEL% neq 0 (
    echo Failed to compile.
    pause
) else (
    echo Compilation succeeded.
    cd "./build/"
    start "Program" main.exe
)

