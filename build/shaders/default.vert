#version 330 core

// Inputs
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// Sends to the fragment shader
out vec3 color;

// Can change by using     
// GLuint uniID = glGetUniformLocation(program.GetId(), "scale");
// glUniform1f(uniID, 1);
uniform float scale;

void main()
{
    gl_Position = vec4(aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
    color = gl_Position.xyz;
}