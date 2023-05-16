#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "include/glad/glad.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "shader.h"
#include <iostream>


class ShaderProgram
{
    public:
        ShaderProgram();
        ~ShaderProgram();
        void AttachShader(Shader* shader);
        void Link();
        GLuint GetId();
        void SetActive();
        void SetFloat(const GLchar* uniform, float value);
        void SetInt(const GLchar* uniform, int value);
        void SetVec4(const GLchar* uniform, glm::mat4 vector);
    private:
        GLuint id;
};


#endif // SHADERPROGRAM_H