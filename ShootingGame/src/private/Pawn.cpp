#include "Pawn.h"
#include "ResourceManager.h"
#include <stb_image/stb_image.h>

Pawn::Pawn(glm::vec3 position, glm::vec3 size, float playerSpeed) 
	: position(position), size(size), baseEyeHeight(1.5f * size.y / 3), speed(playerSpeed) {
	
	fpsCamera = new CameraComponent(glm::vec3(0, baseEyeHeight, 0));
	fpsCamera->speed = speed;
	
	
	gunMesh = new Model("src/assets/models/Gun/acr.obj");
}

Pawn::~Pawn() {
	delete fpsCamera;
	delete gunMesh;
}

void Pawn::processMovement(EMovement direction, float deltaTime) {
	fpsCamera->processMovement(direction, deltaTime, baseEyeHeight);
	position = fpsCamera->getWorldPosition();
	position.y -= baseEyeHeight;
}

void Pawn::mouseInput(float xoffset, float yoffset, bool bConstrainPitch) {
	fpsCamera->processLook(xoffset, yoffset, bConstrainPitch);
	rotation = fpsCamera->rotation;
}

void Pawn::update(float deltaTime) {
	//std::cout << "Position = " << position.x << ", " << position.y << ", " << position.z << "\n";
	//std::cout << "Camera Pos = " << fpsCamera->getWorldPosition().x << ", " << fpsCamera->getWorldPosition().y << ", " << fpsCamera->getWorldPosition().z << "\n";
}

void Pawn::render() {
	Shader gunShader = ResourceManager::getShader("Gun");
	gunShader.use();
	glm::mat4 model = glm::mat4(1.f);
	glm::vec3 offset = glm::vec3(-.2f, -1.1f, -2.f);
	gunShader.setUnifromMat4f("view", glm::lookAt(fpsCamera->getWorldPosition(), fpsCamera->getWorldPosition() + offset, glm::vec3(0,1,0)));

	model = glm::translate(model, fpsCamera->getWorldPosition() + glm::vec3(.2f, -.2f, 0.f));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
	model = glm::rotate(model, glm::radians(180.f), glm::vec3(1.f, 0.f, 0.f));
	model = glm::rotate(model, glm::radians(-185.f), glm::vec3(0.f, 1.f, 0));

	model = glm::rotate(model, glm::radians(180.f), glm::vec3(1.f, 0.f, 0.f));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
	model = glm::rotate(model, glm::radians(10.f), glm::vec3(0.f, 1.f, 0.f));

	model = glm::rotate(model, glm::radians(20.f), glm::vec3(1.f, 0.f, 0.f));



	model = glm::scale(model, glm::vec3(.6f));
	gunShader.setUnifromMat4f("model", model);
	gunMesh->Draw(gunShader);
	
}