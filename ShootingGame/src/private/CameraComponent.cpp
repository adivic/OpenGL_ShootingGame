#include "CameraComponent.h"

void CameraComponent::updateCameraVectors() {
	glm::vec3 frontDir;
	frontDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	frontDir.y = sin(glm::radians(pitch));
	frontDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(frontDir);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

CameraComponent::CameraComponent(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: front(glm::vec3(0.f,0.f,-1.f)), speed(SPEED), sensitivity(SENSITIVITY), fov(FOV) {

	this->position = position;
	worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	updateCameraVectors();
}

CameraComponent::CameraComponent(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
	: front(glm::vec3(0.f,0.f,-1.f)), speed(SPEED), sensitivity(SENSITIVITY), fov(FOV) {
	position = glm::vec3(posX, posY, posZ);
	worldUp = glm::vec3(upX, upY, upZ);
	this->yaw = yaw;
	this->pitch = pitch;
	updateCameraVectors();
}

void CameraComponent::processMovement(EMovement direction, float deltaTime) {
	float velocity = speed * deltaTime;
	switch (direction) {
		case EMovement::FORWARD:
			position += front * velocity;
			break;
		case EMovement::BACKWARD:
			position -= front * velocity;
			break;
		case EMovement::LEFT:
			position -= right * velocity;
			break;
		case EMovement::RIGHT:
			position += right * velocity;
			break;	
	}
	position.y = 0;
}

void CameraComponent::processLook(float xoffset, float yoffset, bool bConstrainPitch) {
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (bConstrainPitch) {
		if (pitch > 89.f)
			pitch = 89.f;
		if (pitch < -89.f)
			pitch = -89.f;
	}
	updateCameraVectors();
}

void CameraComponent::processScroll(float yoffset) {
	fov -= yoffset;
	if (fov < 1.f)
		fov = 1.f;
	if (fov > FOV)
		fov = FOV;
}
