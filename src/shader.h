#ifndef SHADER_H
#define SHADER_H

#include "include/glad/glad.h"
#include <fstream>
#include <iostream>


class Shader
{
    public:
        Shader(const char* filePath, GLenum shaderType );
        ~Shader();
        GLuint GetId();
    private:
        GLuint id;
        const GLchar* GetDataFromFile(const char* filePath);
};



#endif // SHADER_H