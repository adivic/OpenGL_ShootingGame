#include "Weapon.h"
#include <stb_image/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Components/CameraComponent.h"
#include "ResourceManager.h"

Weapon::Weapon() : Actor() {
	init();
}

Weapon::Weapon(glm::vec3 pos, FRotator rot, glm::vec3 size) : Actor(pos, rot, size) {
	init();
}

Weapon::~Weapon() {
	delete weaponMesh;
}

void Weapon::init() {
	stbi_set_flip_vertically_on_load(true);
	weaponMesh = new Model("src/assets/models/Gun/acr.obj");
}

void Weapon::update(float deltaTime) {}

void Weapon::render() {
	Shader gunShader = ResourceManager::getShader("Gun");
	gunShader.use();
	// Look at matrix: (camera_position, object_position, world_Up)
	glm::mat4 view = glm::lookAt(position - glm::vec3(.2f, -.2f, 0.f), position, glm::vec3(0, 1, 0));
	gunShader.setUnifromMat4f("view", view);

	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, position + glm::vec3(-0.3f, .1f, .2f));

	model = glm::rotate(model, glm::radians(rotation.Pitch), glm::vec3(0.f, 1.f, 0.f));
	model = glm::rotate(model, glm::radians(rotation.Yaw), glm::vec3(1.f, 0.f, 0.f));
	model = glm::rotate(model, glm::radians(rotation.Roll), glm::vec3(0.f, 0.f, 1.f));

	model = glm::scale(model, glm::vec3(.6f));
	gunShader.setUnifromMat4f("model", model);
	weaponMesh->Draw(gunShader);
}
