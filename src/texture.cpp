#include "texture.h"



unsigned char* GetImageFromFile(const char* filePath, int &width, int &height)
{
    //stbi_set_flip_vertically_on_load(true);

    int nrChannels;
    unsigned char* temp = stbi_load(filePath, &width, &height, &nrChannels, 0);
    return temp;
}

Texture::Texture()
{
    glGenTextures(1, &this->id);

    this->Bind();
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
    glDeleteTextures(1, &this->id);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::GetId()
{
    return this->id;
}


void Texture::GenerateTexture(const char* filePath)
{
    this->Bind();

    int width, height;

    unsigned char* data = nullptr;
    data = GetImageFromFile(filePath, width, height);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Couldnt load image" << std::endl;
    }

    stbi_image_free(data);
}