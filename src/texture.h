#include "include/glad/glad.h"

#include "include/stb_image/stb_image.h"
#include <iostream>
unsigned char* GetImageFromFile(const char* filePath, int &width, int &height);

class Texture
{
    public:
        Texture();
        ~Texture();
        void Bind();
        void Unbind();
        void GenerateTexture(const char* filePath);
        GLuint GetId();
    private:
        GLuint id;
};


