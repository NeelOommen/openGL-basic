#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VertexBufferClass.h"
#include "IndexBufferClass.h"'
#include "VertexArrayClass.h"


#define height 800
#define width 800

//temporary data for our basic triangles
GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
};

GLuint indices[] = {
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
};


int main() {

	glfwInit();

	//Setup
	//OpenGL version 3.3, Core Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//Creating our window
	GLFWwindow* window = glfwCreateWindow(width,height,"openGL Basics Window",NULL,NULL);

	//Error handling for if window creation fails5
	if (window == NULL) {
		std::cout << "Failed to create a valid window instance.";
		glfwTerminate();
		return -1;
	}

	//If window created is valid, make it the current "context" for openGL to work on (useful if multiple openGL instances are running)
	glfwMakeContextCurrent(window);

	//Using GLAD to load actual openGL functions
	gladLoadGL();

	//Telling openGL the area where it is allowed to operate 
	//In this case we have passed it (0,0) <- Bottom Left corner, to (width,height) <- Top right corner, giving it our whole window
	glViewport(0, 0, width, height);

	//Creating our shaders
	Shader shader("default.vert","default.frag");

	//Setting up VBO's and VAO's and IBO's
	VAO vao1;
	vao1.bind();

	VBO vbo1(vertices,sizeof(vertices));
	IBO ibo1(indices,sizeof(indices));

	//linking the layout and vbo to the vao
	vao1.linkLayout(vbo1,0);

	vao1.unbind();
	vbo1.unbind();
	ibo1.unbind();
	
	//Setting a default background colour for now
	//sets the colour which is used when we clear our buffers
	//Setting a cyan colour as the clear colour using format (r,g,b,a), using normalized values
	//(cyan is an arbitrary chocie, it could be any colour)
	glClearColor(0.0f, 0.93f, 1.0f, 1.0f);
	//Actually clearing the buffer (here we are clearing the back buffer)
	glClear(GL_COLOR_BUFFER_BIT);
	//Swapping the Back Buffer and the Front Buffer (the front buffer is the one displayed on screen)
	glfwSwapBuffers(window);

	//loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.93f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.activateShader();

		//Bind buffers to be used
		vao1.bind();
		
		//Draw Call
		//glDrawArrays(GL_TRIANGLES,0,3); this draw call is for raw vertex data only, no IBO
		//IBO draw call
		glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
		
		//Swap Buffers to get the image on screen
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//cleanup
	vao1.unbind();
	vbo1.unbind();
	ibo1.unbind();
	shader.deactivateShader();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}