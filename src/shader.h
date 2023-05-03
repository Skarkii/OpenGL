#ifndef SHADER_H
#define SHADER_H

#include "include/glad/glad.h"
#include <iostream>




class Shader
{
    public:
        Shader(const GLchar vertFile,  GLchar fragFile);
    private:
        GLuint id;
};



#endif // SHADER_H