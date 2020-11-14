#pragma once
#ifndef PAWN_H
#define PAWN_H

#include <glm/gtc/matrix_transform.hpp>
#include <irrKlang.h>
#include "Components/CameraComponent.h"
#include "Weapon.h"

class Pawn {

private:
	//irrklang::ISoundEngine* soundEngine;

	void playFootsteps();

protected:
	glm::vec3 position;
	glm::vec3 size;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float baseEyeHeight; //initial position of the camera
	CameraComponent* fpsCamera;

	// Speed of player
	float speed;
	FRotator rotation;
	Weapon* weapon;

public:
	Pawn(glm::vec3 position, glm::vec3 size = glm::vec3(1.f, 2.f, 1.f), float playerSpeed = SPEED);
	~Pawn();

	void processMovement(EMovement direction, float deltaTime);
	void mouseInput(float xoffset, float yoffset, bool bConstrainPitch = true);
	void update(float deltaTime);
	void render();

	void sprint(bool bStart);
	void fire();

	inline CameraComponent* getPlayerCamera() { return fpsCamera; }
	inline FRotator getPlayerRotation() { return rotation; }
	inline glm::vec3 getForwardVector() { return front; }
	inline glm::vec3 getPosition() { return position; }
	inline glm::vec3 getSize() { return size; }
	inline float getBaseEyeHeight() { return baseEyeHeight; }
	inline float getMovementSpeed() { return speed; }
	inline Weapon* getWeapon() { return weapon; }

	bool bAiming = false;
	bool bSprinting = false;
};

#endif // !PAWN_H
