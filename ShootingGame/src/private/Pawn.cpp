#include "Pawn.h"
#include <GLFW/glfw3.h>
#include "ResourceManager.h"
#include <stb_image/stb_image.h>

void Pawn::playFootsteps() {
	if (!soundEngine->isCurrentlyPlaying("src/assets/audio/Footstep01.wav")) {
		 soundEngine->play3D("src/assets/audio/Footstep01.wav", irrklang::vec3df(0, 0, 0));
	}
	if (!soundEngine->isCurrentlyPlaying("src/assets/audio/Footstep02.wav")) {
		soundEngine->play3D("src/assets/audio/Footstep02.wav", irrklang::vec3df(0, 0, 0));
	}
}

Pawn::Pawn(glm::vec3 position, glm::vec3 size, float playerSpeed)
	: position(position), size(size), baseEyeHeight(1.5f * size.y / 3), speed(playerSpeed) {
	
	fpsCamera = new CameraComponent(glm::vec3(0, baseEyeHeight, 0));
	fpsCamera->speed = speed;
	
	glm::vec3 gunLocation = fpsCamera->getWorldPosition() + glm::vec3(.2f, -.2f, 0.f);
	weapon = new Weapon(gunLocation, FRotator(40.f, 95.f, 2.f));

	soundEngine = irrklang::createIrrKlangDevice();
}

Pawn::~Pawn() {
	delete fpsCamera;
	delete weapon;
	delete soundEngine;
}

void Pawn::processMovement(EMovement direction, float deltaTime) {
	fpsCamera->processMovement(direction, deltaTime, baseEyeHeight);
	position = fpsCamera->getWorldPosition();
	position.y -= baseEyeHeight;
	playFootsteps();
}

void Pawn::mouseInput(float xoffset, float yoffset, bool bConstrainPitch) {
	fpsCamera->processLook(xoffset, yoffset, bConstrainPitch);
	rotation = fpsCamera->rotation;
}

void Pawn::update(float deltaTime) { weapon->update(deltaTime); }

void Pawn::render() {
	weapon->render();
	if (bSprinting)
		weapon->setActorRotation(FRotator(60.f, 120.f, 10.f));
	else 
		weapon->setActorRotation(FRotator(40.f, 95.f, 2.f));
}

void Pawn::sprint(bool bStart) {
	bSprinting = bStart;
	if (bStart)
		speed = fpsCamera->speed = 7.f;
	 else 
		speed = fpsCamera->speed = SPEED;
}

/* TODO Camera Shake */
void Pawn::fire() {
	weapon->fire();
}
