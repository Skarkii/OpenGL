#ifndef SHADER_H
#define SHADER_H

#include "include/glad/glad.h"
#include <iostream>


class Shader
{
    public:
        Shader(const char* shaderInfo, GLenum shaderType );
        ~Shader();
        GLuint GetId();
    private:
        GLuint id;
};



#endif // SHADER_H