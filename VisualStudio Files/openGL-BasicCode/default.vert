#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 iColour;
layout (location=2) in vec2 aTex;
layout (location=3) in vec3 aNormal;

out vec3 colour;
out vec2 texCoord;
out vec3 Normal;
out vec3 crntPos;

//CPU calculated camera matrix
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	crntPos = vec3(model * vec4(aPos, 1.0f));
	gl_Position = camMatrix * vec4(crntPos,1.0f);
	colour = iColour;
	texCoord = aTex;
	Normal = aNormal;
}