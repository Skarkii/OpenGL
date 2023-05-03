#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "include/glad/glad.h"
#include "shader.h"
#include <iostream>


class ShaderProgram
{
    public:
        ShaderProgram();
        void attachShader(Shader* shader);
        void linkProgram();
        void setActive();
    private:
        GLuint id;
};


#endif // SHADERPROGRAM_H