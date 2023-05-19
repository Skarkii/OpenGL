#include "shader.h"

const GLchar* GetDataFromFile(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Couldn't open file " << filename << std::endl;
        return nullptr;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    file.close();

    char* data = new char[content.size() + 1];
    std::copy(content.begin(), content.end(), data);
    data[content.size()] = '\0';

    return data;
}

Shader::Shader(const char* filePath, GLenum shaderType )
{
    this->id = glCreateShader(shaderType);
    std::cout << "[SHADER (" << this->id << ")] Created" << std::endl;
    const char* data = GetDataFromFile(filePath);
    glShaderSource(this->id, 1, &data, NULL);
    glCompileShader(this->id);

    int success;
    char infoLog[512];

    glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);

    // std::cout << data << std::endl;


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