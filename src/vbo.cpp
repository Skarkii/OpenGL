#include "vbo.h"
#include <iostream>


VBO::VBO()
{
    glGenBuffers(1, &this->id);  
    std::cout << "[VBO (" << this->id << ")] created" << std::endl;
}


VBO::~VBO()
{
    glDeleteBuffers(1, &this->id); 
}

GLuint VBO::GetId()
{
    return this->id;
}

void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}



void VBO::Bind()
{
    //bind to several buffers at once as long as they have a different buffer type.
    //bind  buffer to the GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VBO::SetBufferData(float* vertices, size_t size)
{   
/*
    GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    GL_STATIC_DRAW: the data is set only once and used many times.
    GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
*/
    this->Bind();

    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // this->Unbind();
}