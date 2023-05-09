#version 330 core
out vec4 FragColor;
   
//Recieves from vertex shader
in vec3 color;

void main()
{
    FragColor = vec4(abs(color.x), abs(color.y), abs(color.z), 1.0f);
}