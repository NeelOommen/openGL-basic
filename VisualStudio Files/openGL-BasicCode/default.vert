#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 iColour;
layout (location=2) in vec2 aTex;

out vec3 colour;
out vec2 texCoord;

//CPU calculated camera matrix
uniform mat4 camMat;

void main()
{
	gl_Position = camMat * vec4(aPos,1.0);
	colour = iColour;
	texCoord = aTex;
}