#pragma once
#include "Camera.h"
#include <glew.h>
#include <vector>
#include <glm\glm.hpp>

using namespace glm;
using namespace std;

class Shape
{
	public:
		Shape(GLfloat _vertices[], GLsizei _numVerts, GLuint _programIndex);
		Shape(GLuint _programIndex, vector<glm::vec3> vertices, vector<unsigned int> indices);
		~Shape();

		GLuint vertBuff;
		GLuint vertArr;
		GLuint programIndex;
		GLsizei numVerts;
		GLint offsetLoc;
		GLint scaleLoc;
		GLint matrixLoc;
		GLint uniformColorLocation;
		GLsizei numElements;
		vector<glm::vec3> vertices;
	
		//Methods
		void draw(vec3 currentPosition, vec3 currentScale, vec3 rotationAxis, float rotationAngle, vec3 color, Camera* cam);
};

