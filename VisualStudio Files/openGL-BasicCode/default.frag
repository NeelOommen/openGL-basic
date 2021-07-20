#version 330 core
out vec4 FragColor;

in vec3 colour;
in vec2 texCoord;

uniform vec4 lightColour;
uniform sampler2D tex0;

void main()
{
	FragColor = texture(tex0, texCoord) * lightColour;
}