#version 330 core
out vec4 FragColor;

in vec3 colour;
in vec2 texCoord;
in vec3 crntPos;
in vec3 Normal;

uniform vec4 lightColour;
uniform vec3 lightPos;
uniform sampler2D tex0;

void main()
{
	float ambient = 0.20f;
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	FragColor = texture(tex0, texCoord) * lightColour * (diffuse + ambient);
}