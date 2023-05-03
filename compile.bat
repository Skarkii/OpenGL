@echo off
echo Compiling...
set COMPILER= g++
set STANDARD= -std=c++11 -Wall
set INCLUDE= -I./include
set LIBS= -L./src/lib
set OUTPUT= -o ./build/main.exe
set SOURCE= ./src/main.cpp ./src/include/glad/glad.c ./src/vbo.cpp ./src/shader.cpp ./src/shaderProgram.cpp
set LINK= -lglfw3dll -lopengl32 -lgdi32

%COMPILER% %STANDARD% %INCLUDE% %LIBS% %OUTPUT% %SOURCE% %LINK%
if %ERRORLEVEL% neq 0 (
    echo Failed to compile.
    pause
) else (
    echo Compilation succeeded.
)