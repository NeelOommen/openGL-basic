#ifndef SHADER_CLASS_H

#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_data(const char* filename);

class Shader {
public:
	//Reference ID for openGL to refer to the shader program
	GLuint ID;
	//Constructor loads the 2 shaders, compiles them, attaches them to a program and links the program
	Shader(const char* vertFilePath, const char* fragFilePath);

	void activateShader();
	void deactivateShader();
};


#endif // !SHADER_CLASS_H
