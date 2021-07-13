#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VertexBufferClass.h"
#include "IndexBufferClass.h"'
#include "VertexArrayClass.h"


#define height 800
#define width 800

//temporary data for our basic triangles
GLfloat vertices[] = {
	//   x       y       z              r       g       b               texX    texY
		-0.5f,  -0.5f,   0.0f,			1.0f,   0.0f,   0.0f,			0.0f,   0.0f,
		-0.5f,   0.5f,   0.0f,			0.0f,   1.0f,   0.0f,			0.0f,   1.0f,
		 0.5f,   0.5f,   0.0f,			0.0f,   0.0f,   1.0f,			1.0f,   1.0f,
		 0.5f,  -0.5f,   0.0f,			1.0f,   1.0f,   1.0f,			1.0f,   0.0f
};

GLuint indices[] = {
	0,2,1,
	0,3,2
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

	int imgHeight, imgWidth, imgNumColCh;
	//loads raw img data
	//important to set flip to true as stbi loads top left to bottom right, but openGL reads bottom left to top right
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imgTextureBytes = stbi_load("cursed_texture.png",&imgWidth,&imgHeight,&imgNumColCh,0);

	GLuint textureID;
	glGenTextures(1,&textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//rgba is relevant for png format, rgb for jpg
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imgWidth,imgHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,imgTextureBytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	//texture cleanup
	stbi_image_free(imgTextureBytes);
	glBindTexture(GL_TEXTURE_2D,0);

	GLuint textUniformID = glGetUniformLocation(shader.ID,"tex0");
	shader.activateShader();
	glUniform1f(textUniformID,0);

	
	
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
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		shader.activateShader();
		//can only access uniforms of th active shader program
		glUniform1f(scaleUniformID, sin(scaleFactor) * maxScale);
		glBindTexture(GL_TEXTURE_2D,textureID);

		//Bind buffers to be used
		vao1.bind();
		
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
	glDeleteTextures(1,&textureID);
	shader.deactivateShader();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}