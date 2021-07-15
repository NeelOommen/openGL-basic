#include "Camera.h"

Camera::Camera(int w, int h, glm::vec3 pos) {
	Camera::width = w;
	Camera::height = h;
	Position = pos;
}

void Camera::Matrix(float FOVdeg, float nearClipPlane, float farClipPlane, Shader& shader, const char* uniform) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height),nearClipPlane, farClipPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID,uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::inputHandler(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += speed* -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.4f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.1f;
	}
}