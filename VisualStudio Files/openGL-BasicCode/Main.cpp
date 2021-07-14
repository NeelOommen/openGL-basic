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


#define height 800
#define width 800

//temporary data for our basic triangles
GLfloat vertices[] = {
	//   x       y       z              r       g       b               texX    texY
		-0.5f,  0.0f,    0.5f,			0.83f,   0.70f,   0.44f,			0.0f,   0.0f,
		-0.5f,  0.0f,   -0.5f,			0.83f,   0.70f,   0.44f,			0.0f,   1.0f,
		 0.5f,  0.0f,   -0.5f,			0.83f,   0.70f,   0.44f,			1.0f,   1.0f,
		 0.5f,  0.0f,    0.5f,			0.83f,   0.70f,   0.44f,			1.0f,   0.0f,
		 0.0f,  0.8f,    0.0f,			0.92f,   0.86f,   0.76f,			0.5f,   1.0f
};

GLuint indices[] = {
	0, 1, 1,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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
	vao1.linkAttrib(vbo1, 0, 3,GL_FLOAT,  sizeof(float) * 8, (void* )0);
	vao1.linkAttrib(vbo1, 1, 3, GL_FLOAT, sizeof(float) * 8, (void*)(3*sizeof(float)));
	vao1.linkAttrib(vbo1, 2, 2, GL_FLOAT, sizeof(float) * 8, (void*)(6 * sizeof(float)));

	GLuint scaleUniformID = glGetUniformLocation(shader.ID, "scale");


	vao1.unbind();
	vbo1.unbind();
	ibo1.unbind();

	//Loading texture

	texture curTexture("cursed_texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	curTexture.textureUniformUnit(shader, "tex0", 0);

	
	
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
	float scaleFactor = 0.0f;
	float scaleIterator = 0.00f;
	float maxScale = 0.7f;

	float rotation = 0.0f;
	float rotationStep = 0.05f;
	double prevTime = glfwGetTime();

	//Enables the z buffer, so openGL can correctly occlude vertices when they overlap (including primitives)
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.activateShader();
		//can only access uniforms of th active shader program
		glUniform1f(scaleUniformID, sin(scaleFactor) * maxScale);
		curTexture.bind();

		//Bind buffers to be used
		vao1.bind();

		//creating Matrices to perform the necessary 3d transforms

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60) {
			rotation += rotationStep;
			prevTime = crntTime;
		}

		//rotating the model for the 3d effect
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		//moves the camera by the given vec3
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		//sets the projection matrix
		//                      angle                aspect ratio        near plane  far plane
		proj = glm::perspective(glm::radians(45.0f), float(width/height), 0.1f,      100.f);

		//passing the matrices to the vert shader as uniforms
		//note: these uniforms must only be created and set after the shader has been "activated" or bound
		GLuint modelMatUniform = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelMatUniform, 1, GL_FALSE, glm::value_ptr(model));
		GLuint viewMatUniform = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(viewMatUniform, 1, GL_FALSE, glm::value_ptr(view));
		GLuint projMatUniform = glGetUniformLocation(shader.ID, "proj");
		glUniformMatrix4fv(projMatUniform, 1, GL_FALSE, glm::value_ptr(proj));
		//the gl_position formula is proj*view*model*vec4(position,1.0)
		// the order is important as matrix multiplication is not 
		
		//Draw Call
		//glDrawArrays(GL_TRIANGLES,0,3); this draw call is for raw vertex data only, no IBO
		//IBO draw call
		glDrawElements(GL_TRIANGLES,(sizeof(indices)/sizeof(GLuint)),GL_UNSIGNED_INT,0);
		
		//Swap Buffers to get the image on screen
		glfwSwapBuffers(window);

		glfwPollEvents();
		scaleFactor += scaleIterator;
	}

	//cleanup
	vao1.unbind();
	vbo1.unbind();
	ibo1.unbind();
	curTexture.deleteTexture();
	shader.deactivateShader();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}