#ifndef EBO_H
#define EBO_H

#include "include/glad/glad.h"
#include <iostream>

class EBO
{
    public:
        EBO();
        ~EBO();
        void Bind();
        void Unbind();
        void SetBufferData(unsigned int* indices, size_t size);
    private:
        GLuint id;
};



#endif // EBO_H