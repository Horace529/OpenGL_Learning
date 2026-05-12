#version 330 core
in vec3 ourColor; // the input variable from the vertex shader (same name and same type)
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D ourTexture; // the texture sampler, we will set this in the OpenGL code

void main()
{
   //FragColor= texture(ourTexture, TexCoord);// set the output color of the pixel
   FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
}