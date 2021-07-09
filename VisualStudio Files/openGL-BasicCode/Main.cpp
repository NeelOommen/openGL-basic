#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define height 800
#define width 800

//making shaders for temporary usage
const char* vertexShaderCode = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\n\0";

const char* fragmentShaderCode = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f,0.3f,0.02f,1.0f);\n"
"}\n\0";
//

int main() {

	glfwInit();

	//Setup
	//OpenGL version 3.3, Core Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//temporary data for basic triangle
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f* float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.0f, - 0.5f * float(sqrt(3)) / 3, 0.0f
	};

	GLuint indices[] = {
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};

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
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderCode,NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderCode,NULL);
	glCompileShader(fragmentShader);

	//Creating a program to pass to the GPU
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);

	//cleaning up by deleting the individual shaders now that they have been attached to the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Setting up VBO's and VAO's
	GLuint VAO, VBO, IBO;

	glGenVertexArrays(1,&VAO);

	glGenBuffers(1,&VBO);
	glGenBuffers(1, &IBO);
	
	//Binding simply makes that object the current "focus" of openGL, and all modifications will be made to it while it remains binded
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


	glVertexAttribPointer(0,sizeof(float),GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	//for safety, we will unbind the vao and vbo so we don't unknowingly modify them
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	//Important to unbind IBO after the vao, as otherwise it gets removed from the vao
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);



	
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
		glUseProgram(shaderProgram);

		//Bind buffers to be used
		glBindVertexArray(VAO);
		
		//Draw Call
		//glDrawArrays(GL_TRIANGLES,0,3); this draw call is for raw vertex data only, no IBO
		//IBO draw call
		glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
		
		//Swap Buffers to get the image on screen
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//cleanup
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&IBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}