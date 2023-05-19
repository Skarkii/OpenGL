#ifndef VBO_H
#define VBO_H

#include "include/glad/glad.h"
#include <iostream>

/**
 * @brief Represents a Vertex Buffer Object
 * 
 * A Vertex Buffer Object is a buffer object that stores vertex data such as positions, 
 * colors, normals, texture coordinates, and any other attributes that define the geometry of a 3D object.
 * 
 */
class VBO
{
    public:
        /**
         * @brief Default constructor.
         * 
         * Constructs a new Vertex Buffer Object
         */
        VBO();

        VBO(float* vertices, size_t size);


        /**
         * @brief Default deconstructor.
         * 
         * Removes the Vertex Buffer Object
         */
        ~VBO();

        /**
        * @brief Binds a buffer object to a target buffer binding point.
        * 
        * 
        * @param 
        * @return 
        */
        void Bind();

        void Unbind();

        GLuint GetId();

        void SetBufferData(float* vertices, size_t size);

    private:
        GLuint id;
};



#endif // VBO_H