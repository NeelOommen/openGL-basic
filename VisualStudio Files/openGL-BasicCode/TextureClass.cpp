#include "TextureClass.h"

void texture::bind() {
	glBindTexture(type,ID);
}

void texture::unbind() {
	glBindTexture(type,0);
}

void texture::deleteTexture() {
	glDeleteTextures(1,&ID);
}

texture::texture(const char* textureFilePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	type = texType;
	glGenTextures(1,&ID);
	glActiveTexture(slot);
	glBindTexture(type, ID);

	//Set "filtering parametes"
	//nearest mode uses the pixel values directly (more pixelised), linear interpolates the pixels (blurrier, but smooth transitions)
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Set "clamping" mode
	//Textures use rst coordinates instead of xyz
	//repeat mode just repeats the textures if the texture is too small, can also use mirrored or clamped
	//these wrapping modes can be set individually for all of the axis
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Loading images/textures using stbi
	stbi_set_flip_vertically_on_load(true);
	int height, width, colCh;
	unsigned char* data = stbi_load(textureFilePath, &width, &height, &colCh,0);

	//loading into texture object
	glTexImage2D(type, 0, format, width, height, 0, format, pixelType, data);
	glGenerateMipmap(type);

	stbi_image_free(data);
	glBindTexture(type, ID);
}

void texture::textureUniformUnit(Shader &shader, const char* uniform, GLuint unit) {
	GLuint uniformID = glGetUniformLocation(shader.ID, uniform);
	shader.activateShader();
	glUniform1f(uniformID, unit);
	//DO NOT DEACTIVATE THE SHADER HERE, OR AT ALL UNTIL YOU ARE DONE USING IT COMPLETELY, AS IT IS GONE PERMANENTLY AS WE USE DELETESHADER
	//rip my sanity trying to find this bug, going on 72 hrs now ( ._.)
}
