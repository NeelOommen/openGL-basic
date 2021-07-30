#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

 

#include "shaderClass.h"
#include "VertexBufferClass.h"
#include "IndexBufferClass.h"'
#include "VertexArrayClass.h"
#include "TextureClass.h"
#include "Camera.h"


#define height 800
#define width 800

//temporary data for our basic triangles
GLfloat vertices[] = {
	// Positions                      Colour                    Texture Coord                Normals
	-0.5f,  0.0f,  0.5f,		 0.83f,  0.70f,  0.44f,			 0.0f,  0.0f,			 0.0f, -1.0f,  0.0f, //bottom face
	-0.5f,  0.0f, -0.5f,		 0.83f,  0.70f,  0.44f,			 0.0f,  0.0f,			 0.0f, -1.0f,  0.0f, //bottom face
	 0.5f,  0.0f, -0.5f,		 0.83f,  0.70f,  0.44f,			 0.0f,  0.0f,			 0.0f, -1.0f,  0.0f, //bottom face
	 0.5f,  0.0f,  0.5f,		 0.83f,  0.70f,  0.44f,			 0.0f,  0.0f,			 0.0f, -1.0f,  0.0f, //bottom face

	-0.5f,  0.0f,  0.5f,		 0.83f,  0.70f,  0.44f,			 0.0f,  0.0f,			-0.8f,  0.5f,  0.0f, //left face
	-0.5f,  0.0f, -0.5f,		 0.83f,  0.70f,  0.44f,			 5.0f,  0.0f,			-0.8f,  0.5f,  0.0f, //left face
	 0.0f,  0.8f,  0.0f,		 0.92f,  0.86f,  0.76f,			 2.5f,  5.0f,			-0.8f,  0.5f,  0.0f, //left face

	-0.5f,  0.0f, -0.5f,		 0.83f,  0.70f,  0.44f,          5.0f,  0.0f,			 0.0f,  0.5f, -0.8f, //non-facing side
	 0.5f,  0.0f, -0.5f,		 0.83f,  0.70f,  0.44f,			 0.0f,  0.0f,			 0.0f,  0.5f, -0.8f, //non-facing side
	 0.0f,  0.8f,  0.0f,		 0.92f,  0.86f,  0.76f,			 2.5f,  5.0f,			 0.0f,  0.5f, -0.8f, //non-facing side

	 0.5f,  0.0f, -0.5f,		 0.83f,  0.70f,  0.44f,			 0.0f,  0.0f,			 0.8f,  0.5f,  0.0f, //right face
	 0.5f,  0.0f,  0.5f,		 0.83f,  0.70f,  0.44f,			 5.0f,  0.0f,			 0.8f,  0.5f,  0.0f, //right face
	 0.0f,  0.8f,  0.0f,		 0.92f,  0.86f,  0.76f,			 2.5f,  5.0f,			 0.8f,  0.5f,  0.0f, //right face

	 0.5f,  0.0f,  0.5f,         0.83f,  0.70f,  0.44f,			 1.0f,  0.0f,			 0.0f,  0.5f,  0.8f, //Facing Side
	-0.5f,  0.0f,  0.5f,		 0.83f,  0.70f,  0.44f,			 0.0f,  0.0f,			 0.0f,  0.5f,  0.8f, //Facing Side
	 0.0f,  0.8f,  0.0f,		 0.92f,  0.86f,  0.76f,			 0.5f,  0.0f,			 0.0f,  0.5f,  0.8f  //Facing Side
		
};

GLuint indices[] = {
	0, 1, 2,    //Bottom Face I
	0, 2, 3,    //Bottom Face II
	4, 6, 5,    //Left Face
	7, 9, 8,    //Back Face
	10, 12, 11, //Right Face
	13, 15, 14  //Front Face
};

GLfloat lightVert[] = {
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
 	 0.1f, -0.1f, -0.1f, 
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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
	//model shaders
	Shader shaderProgram("default.vert", "default.frag");


	//Setting up VBO's and VAO's and IBO's
	VAO vao1;
	vao1.bind();

	VBO vbo1(vertices,sizeof(vertices));
	IBO ibo1(indices,sizeof(indices));

	//linking the layout and vbo to the vao
	vao1.linkAttrib(vbo1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)(0));
	vao1.linkAttrib(vbo1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	vao1.linkAttrib(vbo1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	vao1.linkAttrib(vbo1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	vao1.unbind();
	vbo1.unbind();
	ibo1.unbind();

	

	//light shaders
	Shader lightShader("light.vert", "light.frag");

	//Creating the light model
	VAO lightVao;
	lightVao.bind();
	 
	VBO lightVBO(lightVert, sizeof(lightVert));
	IBO lightIBO(lightIndices, sizeof(lightIndices));

	lightVao.linkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	
	
	lightVao.unbind();
	lightVBO.unbind();
	lightIBO.unbind();

	

	//creating the model Matrices for the pyramid
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.activateShader();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	
	shaderProgram.activateShader();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	

	

	//Loading texture

	texture curTexture("catTexture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	curTexture.textureUniformUnit(shaderProgram, "tex0", 0);

	
	
	//Setting a default background colour for now
	//sets the colour which is used when we clear our buffers
	//Setting a cyan colour as the clear colour using format (r,g,b,a), using normalized values
	//(cyan is an arbitrary chocie, it could be any colour)
	glClearColor(0.18f, 0.18f, 0.18f, 1.0f);
	//Actually clearing the buffer (here we are clearing the back buffer)
	glClear(GL_COLOR_BUFFER_BIT);
	//Swapping the Back Buffer and the Front Buffer (the front buffer is the one displayed on screen)
	glfwSwapBuffers(window);

	//loop

	//Enables the z buffer, so openGL can correctly occlude vertices when they overlap (including primitives)
	glEnable(GL_DEPTH_TEST);

	//creating a camera object
	Camera camera(width, height, glm::vec3(0.0f,0.0f, 2.0f));

	double startTime;

	float r, g, b;
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		startTime = glfwGetTime();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//calculating the appropriate matrix for the camera to render correctly
		camera.inputHandler(window);
		//updating the camera matrix
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		

		shaderProgram.activateShader();
		camera.setCamMatrix(shaderProgram, "camMatrix");
		curTexture.bind();
		vao1.bind();
		
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColour"), abs(sin(r)), abs(sin(g)), abs(sin(b)), 1.0f);
		//glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColour"), 1.0f, 1.0f, 1.0f,1.0f);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glDrawElements(GL_TRIANGLES, (sizeof(indices) / sizeof(int)), GL_UNSIGNED_INT, 0);

		lightShader.activateShader();
		camera.setCamMatrix(lightShader, "camMatrix");
		lightVao.bind();
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColour"), abs(sin(r)), abs(sin(g)), abs(sin(b)), 1.0f);
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

		r += 0.002f;
		g += 0.1f;
		b += 0.05f;
		
		
		//Swap Buffers to get the image on screen
		glfwSwapBuffers(window);

		//std::cout << "Rough frame Time: " << glfwGetTime() - startTime << std::endl;

		glfwPollEvents();
	}

	//cleanup
	vao1.unbind();
	vbo1.unbind();
	ibo1.unbind();
	curTexture.deleteTexture();
	shaderProgram.deactivateShader();
	lightShader.deactivateShader();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}