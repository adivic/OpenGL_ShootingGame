#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include "Components/Actor.h"
#include "Utility/Model.h"

class Weapon : public Actor {

public:
	Weapon();
	Weapon(glm::vec3 pos, FRotator rot, glm::vec3 size = glm::vec3(0,0,0));
	virtual ~Weapon();

	virtual void init();
	virtual void update(float deltaTime);
	virtual void render();

private:
	Model* weaponMesh;


};

#endif // !WEAPON_H
