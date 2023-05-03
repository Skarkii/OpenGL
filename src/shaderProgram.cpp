#include "shaderProgram.h"


ShaderProgram::ShaderProgram()
{
    this->id = glCreateProgram();
    std::cout << "[SHADER PROGRAM (" << this->id << ")] Created" << std::endl;
}

void ShaderProgram::attachShader(Shader* shader)
{
    glAttachShader(this->id, shader->getId());
    std::cout << "[SHADER (" << shader->getId() << ")] Attached to [SHADER PROGRAM(" << this->id << ")]" << std::endl;
}

void ShaderProgram::linkProgram()
{
    glLinkProgram(this->id);

    int success;
    char infoLog[512];

    glGetShaderiv(this->id, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(this->id, 512, NULL, infoLog);
        std::cout << "[SHADER PROGRAM(" << this->id << ")] link failed, " << infoLog << std::endl;
    }


    std::cout << "[SHADER PROGRAM (" << this->id << ")] Linked" << std::endl;
}

void ShaderProgram::setActive()
{
    glUseProgram(this->id);
}

/*
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);  
After link

*/