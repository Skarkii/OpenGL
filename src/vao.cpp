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

void VAO::LinkVBO(VBO& vbo)
{
    this->Bind();
    vbo.Bind();

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    this->Unbind();
    vbo.Unbind();
}


void VAO::Bind()
{
    glBindVertexArray(this->id);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}
