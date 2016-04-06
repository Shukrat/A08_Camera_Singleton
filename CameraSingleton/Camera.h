#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glew.h>
#include <glfw3.h>
#include <vector>
using namespace glm;

class Camera
{
public:
	Camera();
	~Camera();

	void turn(float dx, float dy, float dt);
	vec3 getLocation();
	vec3 getForward();
	vec3 getLookAt();
	vec3 getUp();
	vec3 getRight();
	void updatePosition(GLFWwindow* window, int key, float dt);

	float yaw;
	float pitch;
	float horizontalAngle;
	float verticalAngle;
	float intialFoV;
	float speed;
	float mouseSpeed;
	vec3 position;
};

