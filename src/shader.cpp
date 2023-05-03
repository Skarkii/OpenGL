#include "shader.h"

Shader::Shader(const char* file, GLenum shaderType )
{
    this->id = glCreateShader(shaderType);
    std::cout << "[SHADER (" << this->id << ")] Created" << std::endl;

    glShaderSource(this->id, 1, &file, NULL);
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

GLuint Shader::getId()
{
    return this->id;
}