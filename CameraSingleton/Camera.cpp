#include "Camera.h"


Camera::Camera(){
	position = vec3(0, 0, 0);
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	intialFoV = 45.0f;
	speed = 1.0f;
	mouseSpeed = 0.1f;
}


Camera::~Camera(){
}

void Camera::turn(float dx, float dy, float dt) {
	horizontalAngle += dx * mouseSpeed * dt;
	verticalAngle += dy * mouseSpeed * dt;
}

vec3 Camera::getLocation() {
	return vec3(0,0,0);
}

vec3 Camera::getForward() {
	return vec3(0, 0, 0);
}

vec3 Camera::getLookAt() {
	glm::vec3 direction = vec3(cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle));
	return direction;
}

vec3 Camera::getUp() {
	vec3 right = getRight();
	vec3 direction = getLookAt();
	vec3 up = cross(right, direction);
	return up;
}

vec3 Camera::getRight() {
	vec3 right;
	right.x = sin(horizontalAngle - 3.14f / 2.0f);
	right.y = 0;
	right.z = cos(horizontalAngle - 3.14f / 2.0f);
	return right;
}

void Camera::updatePosition(GLFWwindow* window, int key, float dt) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && key == GLFW_KEY_W) {
		position += getLookAt() * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && key == GLFW_KEY_A) {
		position -= getRight() * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && key == GLFW_KEY_S) {
		position -= getLookAt() * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && key == GLFW_KEY_D) {
		position += getRight() * speed;
	}
}