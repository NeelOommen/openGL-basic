#include "IndexBufferClass.h"

IBO::IBO(GLuint* indexData, GLsizeiptr size) {
	glGenBuffers(1,&ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,indexData,GL_STATIC_DRAW);
}

void IBO::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID);
}

void IBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void IBO::deleteIBO() {
	glDeleteBuffers(1,&ID);
}