#ifndef VAO_H
#define VAO_H

#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include "vbo.h"
#include <iostream>

class VAO
{
    public:
        VAO();
        ~VAO();
        void Bind();
        void Unbind();
        void LinkVBO(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    private:
        GLuint id;
};



#endif // VAO_H