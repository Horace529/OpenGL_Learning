#version 330 core
in vec3 ourColour; // the input variable from the vertex shader (same name and same type)
out vec4 FragColor;


void main()
{
   FragColor= vec4(ourColour, 1.0); // set the output color of the pixel to ourColor, but use the alpha component from ourColor
} 