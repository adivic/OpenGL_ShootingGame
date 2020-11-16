#pragma once
#ifndef ACTOR_H
#define ACTOR_H

#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Core/Rotator.h"


class Actor {
protected:
	glm::vec3 position;
	glm::vec3 size;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	FRotator rotation;

	Shader shader;

public:

	Actor();
	Actor(glm::vec3 pos, FRotator rot = FRotator(0.f), glm::vec3 size = glm::vec3(1.f,1.5f,1.f));

	virtual ~Actor() {}

	virtual void init();
	virtual void update(float deltaTime);
	virtual void render();

	/* Getters */
	inline FRotator getPlayerRotation() { return rotation; }
	inline glm::vec3 getForwardVector() { return front; }
	inline glm::vec3 getPosition() { return position; }
	inline glm::vec3 getSize() { return size; }
	inline glm::vec3 getRightVector() { return right; }
	inline glm::vec3 getUpVector() { return up; }

	/* Setters */
	inline void setActorRotation(FRotator rot) { rotation = rot; }
	inline void setForwardVector(glm::vec3 vec) { front = vec; }
	inline void setPosition(glm::vec3 vec) { position = vec; }
	inline void setSize(glm::vec3 vec) { size = vec; }
	inline void setRightVector(glm::vec3 vec) { right = vec; }
	inline void setUpVector(glm::vec3 vec) { up= vec; }

};

#endif // !ACTOR_H
