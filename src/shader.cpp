#include "shader.h"

const char* Shader::GetDataFromFile(const char* filename)
{
    std::ifstream file(filename);

    if(!file.is_open()){
        std::cout << "Couldn't open file " << filename << std::endl;
        return nullptr;
    }

    file.seekg(0, std::ios::end);

    std::string buffer;
    buffer.resize(file.tellg());

    file.seekg(0, std::ios::beg);

    file.read(&buffer[0], buffer.size());

    file.close();
    return buffer.c_str();
}


Shader::Shader(const char* filePath, GLenum shaderType )
{
    this->id = glCreateShader(shaderType);
    std::cout << "[SHADER (" << this->id << ")] Created" << std::endl;
    const char* data = this->GetDataFromFile(filePath);
    glShaderSource(this->id, 1, &data, NULL);
    glCompileShader(this->id);

    int success;
    char infoLog[512];

    glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);


    if(!success)
    {
        glGetShaderInfoLog(this->id, 512, NULL, infoLog);
        std::cout << "[SHADER (" << this->id << ")] failed to compile, " << infoLog << std::endl;
    }
    else
    {
        std::cout << "[SHADER (" << this->id << ")] Compiled successfully" << std::endl;
    }
}

GLuint Shader::GetId()
{
    return this->id;
}

Shader::~Shader()
{
    std::cout << "[SHADER (" << this->id << ")] Removed" << std::endl;
    glDeleteShader(this->id);
}