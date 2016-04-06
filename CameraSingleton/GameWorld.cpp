#include "GameWorld.h"
#include "ShaderHelper.h"
#include "Shape.h"
#include "ModelLoader.h"
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
//MatrixCalc* matrixCalc;
glm::mat4 perspectLookAt;

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

	glUseProgram(program);

	// Put initially rendered stuff here, if you want

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = modelLoader.loadObject("cube2.obj", vertices, uvs, normals);

    cam = Camera::GetInstance();
	model = new Shape(program, vertices, uvs);
	modelManipulator = new GameObject(model, vec3(0, 0, -10), 0.5f, vec3(0, 0, 0), 1.0f, vec3(0, 1, 1), 1, vec3(.1, 0.1, 0.5), true);

	// ---
	return true;
}


void GameWorld::update() {
	float dt = getFrameTime();
	// Update all the things here!
    perspectLookAt = cam->getView();
	modelManipulator->update(dt, perspectLookAt);
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

float GameWorld::getFrameTime() {
	lastFrameTime = glfwGetTime();
	double dt = lastFrameTime - prevTime;
	prevTime = lastFrameTime;
	return dt;
}