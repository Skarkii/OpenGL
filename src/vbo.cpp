#include "vbo.h"
#include <iostream>


VBO::VBO()
{
    glGenBuffers(1, &this->id);  
    std::cout << "[VBO (" << this->id << ")] created" << std::endl;
}


VBO::~VBO()
{

}


void VBO::bind()
{
    //bind to several buffers at once as long as they have a different buffer type.
    //bind  buffer to the GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VBO::setBufferData(float vertices[])
{
/*
    GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    GL_STATIC_DRAW: the data is set only once and used many times.
    GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
*/
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}