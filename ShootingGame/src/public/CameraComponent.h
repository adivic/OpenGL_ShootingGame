#pragma once
#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr float YAW = -90.f;
constexpr float PITCH = 0.f;
constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = .1f;
constexpr float FOV = 45.f;

enum class EMovement {FORWARD, BACKWARD, LEFT, RIGHT};

class CameraComponent {
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	void updateCameraVectors();

public:
	float pitch;
	float yaw;
	float speed;
	float sensitivity;
	float fov;

	CameraComponent(glm::vec3 position = glm::vec3(0.f,0.f,0.f), glm::vec3 up = glm::vec3(0.f, 1.f, 0.f), float yaw = YAW, float pitch = PITCH);
	CameraComponent(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);


	inline glm::vec3 getWorldPosition() { return position; }
	inline glm::vec3 getForwardVector() { return front; }
	inline glm::mat4 getViewMatrix() { return glm::lookAt(position, position + front, up); }

	void processMovement(EMovement direction, float deltaTime);
	void processLook(float xoffset, float yoffset, bool bConstrainPitch = true);
	void processScroll(float yoffset);
};


#endif // !CAMERA_COMPONENT_H
