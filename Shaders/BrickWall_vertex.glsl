#version 330 core
layout (location = 0) in vec3 aPos; //set the ID for positions as 0
layout(location = 1) in vec3 aColor;//set the ID for colors as 1
layout(location = 2) in vec2 aTexCoord;//set the ID for texture coordinates as 2

out vec3 ourColour;
out vec2 TexCoord;
void main()
{
	gl_Position = vec4(aPos, 1.0); //aPos is a vec3, we need to convert it to a vec4 by adding 1.0 as the w component
	ourColour = aColor; //pass the color to the fragment shader
	TexCoord = aTexCoord; //pass the texture coordinates to the fragment shader
}