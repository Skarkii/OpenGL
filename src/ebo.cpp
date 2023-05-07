#include "ebo.h"

EBO::EBO()
{
    glGenBuffers(1, &this->id);
    std::cout << "[EBO (" << this->id << ")] created" << std::endl;
}

void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
}

void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::SetBufferData(unsigned int* indices, size_t size)
{
    this->Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    // this->Unbind();
}

EBO::~EBO()
{
    glDeleteBuffers(1, &this->id);
}