#include "VertexArrayClass.h"

VAO::VAO() {
	glGenVertexArrays(1,&ID);
}

void VAO::linkLayout(VBO vbo, GLuint layoutIndex) {
	vbo.bind();
	glVertexAttribPointer(layoutIndex, 3,GL_FLOAT,GL_FALSE,0,(void*)0);
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