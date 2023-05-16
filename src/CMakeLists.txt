cmake_minimum_required(VERSION 3.21)
set( CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe" )
set( CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe" )

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set (CMAKE_CXX_FLAGS "-std=c++11")

project (OpenGL)

ADD_LIBRARY(Module
    main.cpp
    include/glad/glad.c
    ebo.cpp
    inputHandler.cpp
    render.cpp
    shader.cpp
    shaderProgram.cpp
    texture.cpp
    vao.cpp
    vbo.cpp
)



target_link_libraries(Module
    -lopengl32
    -lgdi32
    -static-libgcc 
    -static-libstdc++
    ${CMAKE_SOURCE_DIR}/lib/libglfw3.a
)
ADD_EXECUTABLE(OpenGL 
    main.cpp
    include/glad/glad.c
    ebo.cpp
    inputHandler.cpp
    render.cpp
    shader.cpp
    shaderProgram.cpp
    texture.cpp
    vao.cpp
    vbo.cpp
)

target_link_libraries(OpenGL Module)
