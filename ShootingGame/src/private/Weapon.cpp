#include "Weapon.h"
#include <GLFW/glfw3.h>
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
	delete soundEngine;
}

void Weapon::init() {
	soundEngine = irrklang::createIrrKlangDevice();

	stbi_set_flip_vertically_on_load(true);
	weaponMesh = new Model("src/assets/models/Gun/acr.obj");

	muzzleOffset = glm::vec3(.015f, .1f, .5f);

	//fill weaponInfo 
	weaponInfo.ammo = 31;
	weaponInfo.fullMag = 31;
	weaponInfo.maxAmmo = 125;
	weaponInfo.damage = 15.f;
	weaponInfo.fireRate = .1f;

	prepareMuzzleFlash();
}

void Weapon::update(float deltaTime) {
	//Check if player holding fire button to hide the muzzle flash 
	if (glfwGetTime() > canFire && bFiring)
		bFiring = false;
}

void Weapon::render() {
	Shader gunShader = ResourceManager::getShader("Gun");
	gunShader.use();
	shader.setUniform1i("texture_diffuse1", 0);
	glActiveTexture(GL_TEXTURE0);
	Texture tex = ResourceManager::getTexture("Gun");
	tex.bind();

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
	drawMuzzleFlash();
}

void Weapon::reload() {
	if (weaponInfo.maxAmmo > 0) {
		if (weaponInfo.ammo > 0) {
			short difference = weaponInfo.fullMag - weaponInfo.ammo;
			if (weaponInfo.maxAmmo - difference >= 0) {
				weaponInfo.ammo = weaponInfo.fullMag;
				weaponInfo.maxAmmo -= difference;
			} else {
				weaponInfo.ammo += weaponInfo.maxAmmo;
				weaponInfo.maxAmmo = 0;
			}
		} else {
			if (weaponInfo.maxAmmo - weaponInfo.fullMag > 0) {
				weaponInfo.ammo = weaponInfo.fullMag;
				weaponInfo.maxAmmo -= weaponInfo.fullMag;
			} else {
				weaponInfo.ammo = weaponInfo.maxAmmo;
				weaponInfo.maxAmmo = 0;
			}
		}
		soundEngine->play3D("src/assets/audio/reload.wav", irrklang::vec3df(position.x, position.y, position.z));
	}
}

bool Weapon::fire() {
	if (weaponInfo.ammo <= 0) return false;
	if (glfwGetTime() > canFire && !soundEngine->isCurrentlyPlaying("src/assets/audio/reload.wav")) {
		weaponInfo.ammo--;
		bFiring = true;
		std::cout << "Fire() -> " << weaponInfo.ammo << " bullets left\n";
		irrklang::vec3df pos = irrklang::vec3df(position.x, position.y, position.z);
		soundEngine->play3D("src/assets/audio/gun.wav", pos);
		std::cout << "\nTime: " << glfwGetTime() << " CanFire = " << canFire << "\n";
	}
	canFire = glfwGetTime() + weaponInfo.fireRate;
	return true;
}

void Weapon::prepareMuzzleFlash() {
	float quad[] = {
		 -1.0f,  1.0f,  0.0f, 1.0f,
		 -1.0f, -1.0f,  0.0f, 0.0f,
		  1.0f, -1.0f,  1.0f, 0.0f,

		 -1.0f,  1.0f,  0.0f, 1.0f,
		  1.0f, -1.0f,  1.0f, 0.0f,
		  1.0f,  1.0f,  1.0f, 1.0f
	};
	unsigned int muzzleVBO;
	glGenVertexArrays(1, &muzzleVAO);
	glGenBuffers(1, &muzzleVBO);
	glBindVertexArray(muzzleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, muzzleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));	
	glBindVertexArray(0);
}

void Weapon::drawMuzzleFlash() {
	Shader shader = ResourceManager::getShader("MuzzleFlash");
	glBindVertexArray(muzzleVAO);
	shader.use();
	shader.setUniform1i("muzzleFlash", 0);
	shader.setUniform1i("bShow", bFiring);
	glActiveTexture(GL_TEXTURE0);
	Texture tex = ResourceManager::getTexture("MuzzzleFlash");
	tex.bind();
	glm::mat4 view = glm::lookAt(position - glm::vec3(.2f, .2f, 1.f), position, glm::vec3(0, 1, 0));
	shader.setUnifromMat4f("view", view);
	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, position + muzzleOffset);
	model = glm::scale(model, glm::vec3(.1f,.2f,.2f));
	model = glm::rotate(model, glm::radians(70.f), glm::vec3(0, 1, 0));
	shader.setUnifromMat4f("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	model = glm::mat4(1.f);
	model = glm::translate(model, position + muzzleOffset);
	model = glm::scale(model, glm::vec3(.1f, .2f, .2f));
	shader.setUnifromMat4f("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
