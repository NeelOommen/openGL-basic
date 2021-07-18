#ifndef CAMERA_CLASS_H

#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera {
public:
	int width, height;
	
	//all mats are given some default value as they are otherwise constructed as a null matrix
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	bool firstClick = true;

	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	float speed = 0.1f;
	float sensitivity = 100.0f;

	Camera(int w, int h, glm::vec3 pos);

	void updateMatrix(float FOVdeg, float nearClipPlane, float farClipPlane);
	void setMatrix(Shader& shader, const char* uniform);

	void inputHandler(GLFWwindow* window);
};

#endif