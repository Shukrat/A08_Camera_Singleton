#include "Shape.h"
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glew.h>

using namespace std;
using namespace glm;


Shape::Shape(GLfloat _vertices[], GLsizei _numVerts, GLuint _programIndex){
	numVerts = _numVerts;
	programIndex = _programIndex;

	glUseProgram(programIndex);

	glGenVertexArrays(1, &vertArr);
	glBindVertexArray(vertArr);

	glGenBuffers(1, &vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuff);

	GLfloat temp = 1.0f;
	GLsizei numValsPerVert = numVerts * 5; // Determine number of values in array. 2 for x,y. 3 for x,y,z. 5 for x,y,r,g,b. 6 for x,y,z,r,g,b. Etc

	glBufferData(GL_ARRAY_BUFFER, sizeof(temp) * numValsPerVert, _vertices, GL_STATIC_DRAW); // Size of a float (temp) multiplied by number of values in the array
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(temp) * 5, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(temp) * 5, (void*)(sizeof(GL_FLOAT) * 2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	matrixLoc = glGetUniformLocation(programIndex, "worldMatrix");
	uniformColorLocation = glGetUniformLocation(programIndex, "uniformColor");
}

Shape::Shape(GLuint _programIndex, vector<glm::vec3> vertices, vector<unsigned int> indices) {
	programIndex = _programIndex;
	this->vertices = vertices;
	numElements = indices.size();
	
	GLuint vertexBuffer;
	glGenBuffers(0, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &(vertices[0]), GL_STATIC_DRAW);

	GLuint uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &(indices[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float)*3));

	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);

	matrixLoc = glGetUniformLocation(programIndex, "worldMatrix");
	uniformColorLocation = glGetUniformLocation(programIndex, "color");
}

Shape::~Shape(){
	glDeleteVertexArrays(1, &vertArr);
	glDeleteBuffers(1, &vertBuff);
}

void Shape::draw(vec3 currentPosition, vec3 currentScale, vec3 rotationAxis, float rotationAmt, vec3 color, Camera* cam) {
	mat4 worldMatrix = perspective(45.f, 1.f, .01f, 1000.f) * lookAt(cam->position, cam->position+cam->getLookAt(), cam->getUp()) * translate(currentPosition) * scale(currentScale) * rotate(rotationAmt, rotationAxis);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glProgramUniformMatrix4fv(
		programIndex,
		matrixLoc, 
		1, 
		GL_FALSE, 
		&(worldMatrix[0][0]));
	glProgramUniform4f(programIndex, uniformColorLocation, color.r, color.g, color.b, 1);
	glBindVertexArray(vertArr);

	//numVerts = vertices.size();

	//glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}