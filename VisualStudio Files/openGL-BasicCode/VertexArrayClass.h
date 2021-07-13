#ifndef VERTEX_ARRAY_CLASS_H
#define VERTEX_ARRAY_CLASS_H

#include <glad/glad.h>
#include "VertexBufferClass.h"

class VAO {
public:

	//Reference ID for openGL to the VAO
	GLuint ID;
	VAO();

	//Creates and enables the layout for our current vertex data, 3 floats per vertex (would need to be modified if we had more data(colour, normals, etc)).
	void linkAttrib(VBO& vbo,GLuint layoutIndex, GLuint numComponents, GLenum type, GLsizeiptr size, void* offset);
	
	//helper functions
	void bind();
	void unbind();
	void deleteVAO();
};
#endif