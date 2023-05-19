#include "vao.h"

VAO::VAO()
{
    glGenVertexArrays(1, &this->id);
    std::cout << "[VAO (" << this->id << ")] created" << std::endl;
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &this->id);
}

void VAO::LinkVBO(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
    this->Bind();
    vbo.Bind();

    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}


void VAO::Bind()
{
    glBindVertexArray(this->id);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}
