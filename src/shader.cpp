#include "shader.h"

Shader::Shader(const GLchar vertFile,  GLchar fragFile)
{
    this->id = glCreateShader(GL_VERTEX_SHADER);
    std::cout << "Shader created with id " << this->id << std::endl;

    glShaderSource(this->id, 1, &vertFile, NULL);
    glCompileShader(this->id);

}