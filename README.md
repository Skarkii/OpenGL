# OpenGL Project based on https://learnopengl.com/
## What is this repository?
This repo is a place where I upload my progress while learning myself Computer Graphics using OpenGL.

## Installation
This repository requires you to install some dependencies. 

More in depth details of each dependency can be found on https://learnopengl.com/ aswell as their own webpages/repos.
#### Clone the repo
```bash
$ git clone https://github.com/Skarkii/OpenGL.git 
```
#### GLFW
Install the GLFW pre-compiled binaries from https://www.glfw.org/download.html

Extract the **include** folder into **/src** within the project

Extract the contents of the lib folder of the compiler you're using into **/src/lib**

#### Glad
Install glad headers from https://glad.dav1d.de with the following options:
* Langauge: C/C++
* Specification: OpenGL
* gl: Version 3.3
* Profile: Core

Make sure Generate a loader is ticked.

Extract the **include** folder into **/src** and move **/src/glad.c** from the zip to the **/src/include/glad** folder.
Also change row 25 in file **glad.c**
```c++
#include <glad/glad.h>
```
to
```c++
#include "glad.h"
```

#### stb image
Install stb_image.h from https://github.com/nothings/stb/blob/master/stb_image.h

Put this header file into **src/include/stb_image/**

#### GLM
Install glm from https://github.com/g-truc/glm/tags

Extract the folder **/glm/glm** from the zip into **/src/include/**

## Cmake
Change rows 2 and 3 in **/src/CMakeLists.txt** to match your compiler.

#Only a guide for MinGW will be provided:

Navigate to the root directory of the repository.

Run the commands:
```bash
cmake -B build/ -S src/ -G "MinGW Makefiles"
```
Finally to generate the executable run:
```bash
cmake --build build
```
And now a runnable file OpenGL.exe should have been created as **/build/OpenGL.exe**


