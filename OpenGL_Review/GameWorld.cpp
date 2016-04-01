#include "GameWorld.h"
#include "ShaderHelper.h"
#include "Shape.h"
#include "ModelLoader.h"
#include "Camera.h"
#include <iostream>

using namespace std;

vec2 GameWorld::cursorPos = vec2(0, 0);
bool GameWorld::mouseButtonHeld = false;

// Objects
GLuint vertBuffObj;
GLuint vertArrObj;
GLuint program;
ShaderHelper helper;
ModelLoader modelLoader;
vector<Shape*> GameWorld::shapePtrColl = vector<Shape*>(0);
vector<GameObject*> GameWorld::gameObjPtrColl = vector<GameObject*>(0);

// Variables
const GLsizei numVerts = 3;
const GLsizei numIndivVerts = numVerts * 2;

// Delta time variables
double lastFrameTime;
double prevTime = 0;

// Window stuff
GLFWwindow* window;

// Shapes
Shape* triangle;
const GLsizei triVerts = 3;
const GLsizei triIndividVerts = numVerts * 5;

// Model
Shape* model;
GameObject* modelManipulator;

// Camera
Camera* cam;

int objectArrayPos = 0;

// Constructor / Destructor
GameWorld::GameWorld(){
}
GameWorld::~GameWorld(){

}


bool GameWorld::init() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) return false;

	program = helper.loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (program == 0) {
		cout << "Error loading shader program" << endl;
	}

	//helper.setShaderColor(program, "color", 1.0f, 1.0f, 1.0f);

	glUseProgram(program);

	// Put initially rendered stuff here, if you want

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = modelLoader.loadObject("cube2.obj", vertices, uvs, normals);

	cam = new Camera();
	model = new Shape(program, vertices, uvs);
	modelManipulator = new GameObject(model, vec3(0, 0, -10), 0.5f, vec3(0, 0, 0), 1.0f, vec3(0, 1, 1), 1, vec3(.1, 0.1, 0.5), true, cam);

	// ---
	return true;
}


void GameWorld::update() {
	float dt = getFrameTime();
	// Update all the things here!
	modelManipulator->update(dt);
	glfwSetCursorPos(glfwGetCurrentContext(), (800 / 2), (800 / 2));
	// ---
}


void GameWorld::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	// Draw stuff here!
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	modelManipulator->draw();

	// ---
	glFlush();
}


void GameWorld::mouseMove(GLFWwindow* windowPtr, double x, double y)
{
	double xpos, ypos;
	glfwGetCursorPos(windowPtr, &xpos, &ypos);
	float dx = (800 / 2 - xpos);
	float dy = (800 / 2 - ypos);
	cam->turn(dx, dy, getFrameTime());
}


void GameWorld::mouseClick(GLFWwindow* windowPtr, int button, int action, int mods){
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		mouseButtonHeld = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		mouseButtonHeld = false;
	}
}

void GameWorld::keyPress(GLFWwindow* windowPtr, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D) {
		cam->updatePosition(windowPtr, key, getFrameTime());
	}
	if (key == GLFW_KEY_Q) {
		glfwTerminate();
		exit(0);
	}
}


vec2 GameWorld::getCursorPos(GLFWwindow* windowPtr) {
	double xpos, ypos;
	glfwGetCursorPos(windowPtr, &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(windowPtr, &width, &height);
	vec2 cursorPosition;
	cursorPosition.x = 2.0f * ((float)xpos / (float)width) - 1.0f;
	cursorPosition.y = (2.0f * ((float)ypos / (float)height) - 1.0f) * -1.0f;

	return cursorPosition;
}

//void GameWorld::makeTriangle() {
//	for (int i = 0; i < 101; i++) {
//		GLfloat vertPostns[triIndividVerts] = {
//			0.0f, 0.25f, 0.7f, 0.7f, 0.1f,
//			-0.25f, 0.0f, 0.1f, 0.7f, 0.7f,
//			0.25f, 0.0f, 0.7f, 0.1f, 0.7f
//		};
//		triangle = new Shape(vertPostns, triVerts, program);
//		shapePtrColl.push_back(triangle);
//		float zAxisNeg = 0;
//		if (rand() % 2 + 1 == 1) { zAxisNeg = 1; }
//		else { zAxisNeg = -1; }
//		gameObjPtrColl.push_back(new GameObject(shapePtrColl[i],
//			vec3(cursorPos.x, cursorPos.y, 0),  // position
//			0.1f,		         // mass 
//			vec3(0, 0, 0),		 // velocity
//			0.5f,				 // scale
//			vec3(0, 0, zAxisNeg),		 // rotation axis
//			((rand() % 200 - 100) * .01),	// rotation amount
//			vec3(1, 1, 1),       // color
//			false));			 // active?
//	}
//}

float GameWorld::getFrameTime() {
	lastFrameTime = glfwGetTime();
	double dt = lastFrameTime - prevTime;
	prevTime = lastFrameTime;
	return dt;
}