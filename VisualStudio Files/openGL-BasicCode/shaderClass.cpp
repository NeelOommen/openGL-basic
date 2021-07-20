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
	//std::cout << vertShader << std::endl;
	const char* fragShader = fragSource.c_str();
	//std::cout << fragShader << std::endl;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertShader,NULL);
	glCompileShader(vertexShader);
	//to catch errors in the shader as no verification is performed by c++ or visual studio
	compileErrors(vertexShader,"VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragShader,NULL);
	glCompileShader(fragmentShader);
	//to catch errors in the shader as no verification is performed by c++ or visual studio
	compileErrors(fragmentShader,"FRAGMENT");

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

void Shader::compileErrors(unsigned int shader, const char* type) {
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader,1024,NULL,infoLog);
			std::cout << "Shader Compilation Error for: " << type<< "\n" << std::endl;
		}
	}
	else {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Shader Linking Error for: " << type << "\n" << std::endl;
		}
	}
}
