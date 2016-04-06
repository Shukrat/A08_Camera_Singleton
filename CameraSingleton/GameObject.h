#pragma once
#include "Shape.h"
#include <glm\glm.hpp>
using namespace glm;

class GameObject
{
public:
	GameObject(Shape* shapePtr, vec3 position, float mass, vec3 velocity, float scale, vec3 rotationAxis, float rotationAmt, vec3 color, bool a);
	GameObject();
	~GameObject();

	float getScale();
	void update(float dt, glm::mat4 &perspectLookAt);
	void draw();
	void addForce(vec3 force);
	
	// Mass and Active
	float getMass();
	void setActive(bool active);
	void setRest(bool atRest);

	// Velocity
	void setVelocity(vec3 velocity);
	vec3 getVelocity();

	// Position
	void setPosition(vec3 position);
	vec3 getPosition();

	// Globals
	bool active;
	bool atRest;

private:
	Shape* shapePtr;
	vec3 position;
	float mass;
	vec3 velocity;
	float scale;
	vec3 rotationAxis;
	float rotationAmt;
	vec3 force;
	vec3 color;
	mat4 perspectLookAt;
};

