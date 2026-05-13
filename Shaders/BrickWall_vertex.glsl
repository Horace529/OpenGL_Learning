#version 330 core
layout (location = 0) in vec3 aPos; //set the ID for positions as 0
layout(location = 1) in vec3 aColor;//set the ID for colors as 1
layout(location = 2) in vec2 aTexCoord;//set the ID for texture coordinates as 2

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transFormation;

void main()
{
	gl_Position = transFormation * vec4(aPos, 1.0); //aPos is a vec3, we need to convert it to a vec4 by adding 1.0 as the w component
	ourColor = aColor; //pass the color to the fragment shader
	TexCoord = vec2(aTexCoord.x, aTexCoord.y); //pass the texture coordinates to the fragment shader
}