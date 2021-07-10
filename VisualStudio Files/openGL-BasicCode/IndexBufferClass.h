#ifndef INDEX_BUFFER_CLASS_H
#define INDEX_BUFFER_CLASS_H

#include<glad/glad.h>

class IBO {
public:
	//Reference ID for openGL to refer to the IBO
	GLuint ID;
	IBO(GLuint* indexData, GLsizeiptr size);

	//Helper functions
	void bind();
	void unbind();
	void deleteIBO();
};

#endif