#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "include/glad/glad.h"
#include "shader.h"
#include <iostream>


class ShaderProgram
{
    public:
        ShaderProgram();
        ~ShaderProgram();
        void AttachShader(Shader* shader);
        void Link();
        void SetActive();
    private:
        GLuint id;
};


#endif // SHADERPROGRAM_H