#pragma once
#include "GameObject.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glew.h>
#include <glfw3.h>
#include <vector>

using namespace glm;

class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	static bool init();
	static void update();
	static void draw();
	static void mouseClick(GLFWwindow* window, int button, int action, int mods);
	static void mouseMove(GLFWwindow* window, double x, double y);
	static void keyPress(GLFWwindow* windowPtr, int key, int scancode, int action, int mods);
	static vec2 getCursorPos(GLFWwindow* windowPtr);
	
	static bool mouseButtonHeld;

private:
	//static void makeTriangle();
	static float getFrameTime();

	static vec2 cursorPos;
	static vector<Shape*> shapePtrColl;
	static vector<GameObject*> gameObjPtrColl;

};

