#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glew.h>
#include <glfw3.h>
#include <vector>
using namespace glm;

class Camera
{
private:
    static Camera* instance;
    Camera() {
        position = vec3(0, 0, 0);
        horizontalAngle = 3.14f;
        verticalAngle = 0.0f;
        intialFoV = 45.0f;
        speed = 1.0f;
        mouseSpeed = 0.1f;
    };
    Camera(Camera const& other) {
        instance = other.GetInstance();
    };
    Camera& operator=(Camera const& other) {
        instance = other.GetInstance();
    };

public:
    static Camera* GetInstance() {
        if (instance == nullptr) {
            instance = new Camera();
        }
        return instance;
    }
    static void ReleaseInstance() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }

	void turn(float dx, float dy, float dt);
	
    vec3 getLocation();
    void setLocation(vec3 loc);

    mat4 getView();
    mat4 getProjection(bool orthgraphic);

	vec3 getForward();

	vec3 getLookAt();
    void setLookAt(vec3 lookAt);

	vec3 getUp();
    void setUp(vec3 up);

	vec3 getRight();

    void changePitch(float increment);
    void changeRoll(float increment);
    void changeYaw(float increment);

    void moveForward(float increment);
    void moveSideward(float increment);
    void moveVertical(float increment);

	void updatePosition(GLFWwindow* window, int key, float dt);

	float yaw;
	float pitch;
	float horizontalAngle;
	float verticalAngle;
	float intialFoV;
	float speed;
	float mouseSpeed;
	vec3 position;
    mat4 perspectLookAt;
};

