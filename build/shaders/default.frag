#version 330 core
out vec4 FragColor;
   
//Recieves from vertex shader
in vec3 color;
in vec2 TexCoord;

uniform sampler2D backTexture;
uniform sampler2D frontTexture;

void main()
{
    //FragColor = vec4(abs(color.x), abs(color.y), abs(color.z), 1.0f);
    //FragColor = texture(ourTexture, TexCoord) * vec4(color, 1.0);

    FragColor = mix(texture(backTexture, TexCoord), texture(frontTexture, TexCoord), 0.4);

    //FragColor = texture(ourTexture, TexCoord);
}