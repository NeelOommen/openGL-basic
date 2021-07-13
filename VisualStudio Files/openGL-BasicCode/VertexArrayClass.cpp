#include "VertexArrayClass.h"

VAO::VAO() {
	glGenVertexArrays(1,&ID);
}

void VAO::linkAttrib(VBO& vbo, GLuint layoutIndex, GLuint numComponents, GLenum type, GLsizeiptr size, void* offset) {
	vbo.bind();
	glVertexAttribPointer(layoutIndex, numComponents,type,GL_FALSE,size,offset);
	glEnableVertexAttribArray(layoutIndex);
	vbo.unbind();
}

void VAO::bind() {
	glBindVertexArray(ID);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::deleteVAO() {
	glDeleteVertexArrays(1,&ID);
}