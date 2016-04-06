#include "Camera.h"


void Camera::turn(float dx, float dy, float dt) {
	horizontalAngle += dx * mouseSpeed * dt;
	verticalAngle += dy * mouseSpeed * dt;
}

vec3 Camera::getLocation() {
	return vec3(0,0,0);
}
void Camera::setLocation(vec3 loc) {

}

vec3 Camera::getForward() {
	return vec3(0, 0, 0);
}

glm::mat4 Camera::getView() {
    perspectLookAt = perspective(45.f, 1.f, .01f, 1000.f) * lookAt(position, position + getLookAt(), getUp());
    return perspectLookAt;
}

//glm::mat4 Camera::getProjection(bool orthographic) {
//
//}

vec3 Camera::getLookAt() {
	glm::vec3 direction = vec3(cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle));
	return direction;
}
void Camera::setLookAt(vec3 lookAt) {

}

vec3 Camera::getUp() {
	vec3 right = getRight();
	vec3 direction = getLookAt();
	vec3 up = cross(right, direction);
	return up;
}
void Camera::setUp(vec3 up) {

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

void Camera::changePitch(float increment) {

}

void Camera::changeRoll(float increment) {

}

void Camera::changeYaw(float increment) {

}

void Camera::moveForward(float increment) {

}

void Camera::moveSideward(float increment) {

}

void Camera::moveVertical(float increment) {

}

Camera* Camera::instance = nullptr;