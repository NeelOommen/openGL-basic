#include "shaderClass.h"

std::string get_file_data(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string data;
		//set the g pointer to the end of the file to get the size of the file in the next step
		in.seekg(0,std::ios::end);
		//resizes the data string to the size of the shader file
		data.resize(in.tellg());
		//reset the pointer to the beginning of the file to read the contents in
		in.seekg(0,std::ios::beg);
		//read the actual data in
		in.read(&data[0],data.size());
		//close the input stream
		in.close();
		//return the data
		return(data);
	}
	throw(errno);
}

Shader::Shader(const char* vertFilePath, const char* fragFilePath) {
	std::string vertSource = get_file_data(vertFilePath);
	std::string fragSource = get_file_data(fragFilePath);

	const char* vertShader = vertSource.c_str();
	const char* fragShader = fragSource.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertShader,NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragShader,NULL);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID,vertexShader);
	glAttachShader(ID,fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::activateShader() {
	glUseProgram(ID);
}

void Shader::deactivateShader() {
	glDeleteProgram(ID);
}
