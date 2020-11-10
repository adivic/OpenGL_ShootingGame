#include "Components/Actor.h"
Actor::Actor(glm::vec3 pos, FRotator rot, glm::vec3 size) 
	: position(pos), rotation(rot), size(size), front(glm::vec3(0,0,-1.f)) {}

Actor::Actor() 
	: position(glm::vec3(0, 0, 0)), size(glm::vec3(1, 1, 1)), rotation(FRotator(0)),
	front(glm::vec3(0.f, 0.f, -1.f)), worldUp(glm::vec3(0.f, 1.f, 0.f)) {}

void Actor::init() {}

void Actor::update(float deltaTime) {}

void Actor::render() { }
