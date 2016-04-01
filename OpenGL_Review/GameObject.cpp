#include "GameObject.h"
#include "Camera.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

GameObject::GameObject(Shape* shapePtr, vec3 position, float mass, vec3 velocity, float scale, vec3 rotationAxis, float rotationAmt, vec3 color, bool a, Camera* cam) {
	this->shapePtr     = shapePtr;
	this->position     = position;
	this->mass	       = mass;
	this->velocity     = velocity;
	this->scale        = scale;
	this->rotationAxis = rotationAxis;
	this->rotationAmt  = rotationAmt;
	this->color        = color;
	this->active       = a;
	this->atRest       = false;
	this->force        = vec3(0, 0, 0);
	this->cam		   = cam;
}

void GameObject::update(float dt) {
	rotationAmt += dt;
}

void GameObject::draw() {
	if (active) {
		shapePtr->draw(position, vec3(scale, scale, scale), rotationAxis, rotationAmt, color, cam);
	}
}

void GameObject::addForce(vec3 force) {
	this->force += force;
}

float GameObject::getScale() {
	return scale;
}

// Mass
float GameObject::getMass() {
	return mass;
}

void GameObject::setActive(bool active) {
	this->active = active;
}

void GameObject::setRest(bool atRest) {
	this->atRest = atRest;
}

// Velocity
void GameObject::setVelocity(vec3 velocity) {
	this->velocity = velocity;
}

vec3 GameObject::getVelocity() {
	return velocity;
}

// Position
void GameObject::setPosition(vec3 position){
	this->position = position;
}

vec3 GameObject::getPosition() {
	return position;
}