#version 330 core

// Inputs
layout (location = 0) in vec3 localPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

// Sends to the fragment shader
out vec3 color;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(localPosition, 1.0f);
    gl_Position.x *= -1.0f;

    //color = gl_Position.xyz;

    color = aColor;
    TexCoord = aTexCoord;
};                                                    
                                          
                                        