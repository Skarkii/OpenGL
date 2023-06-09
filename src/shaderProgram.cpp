#include "shaderProgram.h"

GLuint ShaderProgram::GetId()
{
    return this->id;
}

ShaderProgram::ShaderProgram()
{
    this->id = glCreateProgram();
    std::cout << "[SHADER PROGRAM (" << this->id << ")] Created" << std::endl;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(this->id);
}

void ShaderProgram::AttachShader(Shader* shader)
{
    glAttachShader(this->id, shader->GetId());
    std::cout << "[SHADER (" << shader->GetId() << ")] Attached to [SHADER PROGRAM(" << this->id << ")]" << std::endl;
}

void ShaderProgram::Link()
{
    glLinkProgram(this->id);

    int success;
    char infoLog[512];

    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->id, 512, NULL, infoLog);
        std::cout << "[SHADER PROGRAM (" << this->id << ")] link failed, " << infoLog << std::endl;
    }
    else
    {
        std::cout << "[SHADER PROGRAM (" << this->id << ")] Linked" << std::endl;
    }


}

void ShaderProgram::SetActive()
{
    glUseProgram(this->id);
}

void ShaderProgram::SetFloat(const GLchar* uniform, float value)
{
    this->SetActive();
    glUniform1f(glGetUniformLocation(this->id, uniform), value);
}

void ShaderProgram::SetInt(const GLchar* uniform, int value)
{
    this->SetActive();
    glUniform1i(glGetUniformLocation(this->id, uniform), value);
}

void ShaderProgram::SetVec4(const GLchar* uniform, glm::mat4 vector)
{
    this->SetActive();
    glUniformMatrix4fv(glGetUniformLocation(this->id, uniform), 1, GL_FALSE, glm::value_ptr(vector));
}