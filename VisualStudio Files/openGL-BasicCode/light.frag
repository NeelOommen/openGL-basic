#version 330 core

uniform vec4 lightColour;

out vec4 FragColor;

void main()
{
	FragColor = lightColour;
}