#include "shader.h"

Shader::Shader(const char* shaderInfo, GLenum shaderType )
{
    this->id = glCreateShader(shaderType);
    std::cout << "[SHADER (" << this->id << ")] Created" << std::endl;

    glShaderSource(this->id, 1, &shaderInfo, NULL);
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