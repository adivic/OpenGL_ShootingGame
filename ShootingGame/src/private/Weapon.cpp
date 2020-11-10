#include "Weapon.h"
#include <stb_image/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Components/CameraComponent.h"
#include "ResourceManager.h"

Weapon::Weapon() : Actor() {

	stbi_set_flip_vertically_on_load(true);
	weaponMesh = new Model("src/assets/models/Gun/acr.obj");

}

Weapon::Weapon(glm::vec3 pos, FRotator rot, glm::vec3 size) : Actor(pos, rot, size) {
	stbi_set_flip_vertically_on_load(true);
	weaponMesh = new Model("src/assets/models/Gun/acr.obj");
}

Weapon::~Weapon() {
	delete weaponMesh;
}

void Weapon::init() {}

void Weapon::update(float deltaTime) {}

void Weapon::render() {
	Shader gunShader = ResourceManager::getShader("Gun");
	gunShader.use();
	glm::mat4 model = glm::mat4(1.f);
	glm::vec3 offset = glm::vec3(-.2f, -1.1f, .0f);

	//position model back to the origin & rotate it with mouse input
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation.Yaw + YAW), glm::vec3(0, -1.f, 0));
	model = glm::rotate(model, glm::radians(rotation.Pitch), glm::vec3(-1.f, 0, 0));

	// transform model back to its position and update its tinity rotation
	model = glm::translate(model, position + offset);
	model = glm::rotate(model, glm::radians(5.f), glm::vec3(0, 1.f, 0));
	model = glm::scale(model, glm::vec3(.6f));

	gunShader.setUnifromMat4f("model", model);
	weaponMesh->Draw(gunShader);
}
