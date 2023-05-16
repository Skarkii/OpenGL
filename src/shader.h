#ifndef SHADER_H
#define SHADER_H

#include "include/glad/glad.h"
#include <fstream>
#include <sstream>
#include <iostream>


const GLchar* GetDataFromFile(const char* filePath);

class Shader
{
    public:
        Shader(const char* filePath, GLenum shaderType );
        ~Shader();
        GLuint GetId();
    private:
        GLuint id;
};
#endif // SHADER_H