#ifndef TEXTURE_CLASS_H

#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include "shaderClass.h"

class texture {
public:
	GLuint ID;
	GLenum type;
	texture(const char* textureFilePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void textureUniformUnit(Shader &shader, const char* uniform, GLuint unit);

	void bind();
	void unbind();
	void deleteTexture();
};

#endif