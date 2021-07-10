#ifndef VERTEX_BUFFER_CLASS_H
#define VERTEX_BUFFER_CLASS_H

#include <glad/glad.h>

class VBO {
public:
	//Reference ID for openGL to the VBO
	GLuint ID;
	VBO(GLfloat* vertexData,GLsizeiptr size);


	//helper functions to simpilfy the frequently repeated tasks
	void bind();
	void unbind();
	void deleteVBO();
};
#endif