#pragma once
#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Rotator.h"

constexpr float YAW = -90.f;
constexpr float PITCH = 0.f;
constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = .1f;
constexpr float FOV = 45.f;

enum class EMovement {FORWARD, BACKWARD, LEFT, RIGHT, UP};

class CameraComponent {
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	void updateCameraVectors();

public:
	FRotator rotation;
	float speed;
	float sensitivity;
	float fov;

	CameraComponent(glm::vec3 position = glm::vec3(0.f,0.f,0.f), glm::vec3 up = glm::vec3(0.f, 1.f, 0.f), FRotator rot = FRotator(YAW, PITCH, 0.f));
	CameraComponent(float posX, float posY, float posZ, float upX, float upY, float upZ, FRotator rot);

	inline void setPosition(glm::vec3 pos) { position = pos; }

	inline glm::vec3 getWorldPosition() const { return position; }
	inline glm::vec3 getForwardVector() const { return front; }
	inline glm::vec3 getRightVector() const { return right; }
	inline glm::vec3 getUpVector() const { return up; }
	inline glm::mat4 getViewMatrix() const { return glm::lookAt(position, position + front, up); }

	void processMovement(EMovement direction, float deltaTime, float offset = 0.f);
	void processLook(float xoffset, float yoffset, bool bConstrainPitch = true);
	void processScroll(float yoffset);
};


#endif // !CAMERA_COMPONENT_H
