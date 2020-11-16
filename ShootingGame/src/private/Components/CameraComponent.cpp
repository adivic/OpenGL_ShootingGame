#include "Components/CameraComponent.h"

void CameraComponent::updateCameraVectors() {
	glm::vec3 frontDir;
	frontDir.x = cos(glm::radians(rotation.Yaw)) * cos(glm::radians(rotation.Pitch));
	frontDir.y = sin(glm::radians(rotation.Pitch));
	frontDir.z = sin(glm::radians(rotation.Yaw)) * cos(glm::radians(rotation.Pitch));
	front = glm::normalize(frontDir);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

CameraComponent::CameraComponent(glm::vec3 position, glm::vec3 up, FRotator rot)
	: front(glm::vec3(0.f,0.f,-1.f)), speed(SPEED), sensitivity(SENSITIVITY), fov(FOV) {

	this->position = position;
	worldUp = up;
	rotation = rot;
	updateCameraVectors();
}

CameraComponent::CameraComponent(float posX, float posY, float posZ, float upX, float upY, float upZ, FRotator rot) 
	: front(glm::vec3(0.f,0.f,-1.f)), speed(SPEED), sensitivity(SENSITIVITY), fov(FOV) {
	position = glm::vec3(posX, posY, posZ);
	worldUp = glm::vec3(upX, upY, upZ);
	rotation = rot;

	updateCameraVectors();
}

void CameraComponent::processMovement(EMovement direction, float deltaTime, float offset) {
	//const float jumpForce = 90.f;
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
		//case EMovement::UP:
		//	velocity *= jumpForce;
		//	position += up * velocity;
		//	break;
	}
	//if(direction != EMovement::UP)
		position.y = offset;
}

void CameraComponent::processLook(float xoffset, float yoffset, bool bConstrainPitch) {
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	rotation.Yaw += xoffset;
	rotation.Pitch += yoffset;

	if (bConstrainPitch) {
		if (rotation.Pitch > 89.f)
			rotation.Pitch = 89.f;
		if (rotation.Pitch < -89.f)
			rotation.Pitch = -89.f;
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
