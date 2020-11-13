#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include <irrKlang.h>
#include "Components/Actor.h"
#include "Utility/Model.h"
#include "Components/ParticleEmitter.h"

struct FWeaponInfo {
	short ammo; // current ammo in the magazine
	short fullMag; // ammo for the full magazine
	short maxAmmo; // max ammo that player owns
	float fireRate; // fire rate of the weapon 
	float damage; // damage that weapon's bullet do on the enemy
};

class Weapon : public Actor {

public:
	Weapon();
	Weapon(glm::vec3 pos, FRotator rot, glm::vec3 size = glm::vec3(0,0,0));
	virtual ~Weapon();

	virtual void init();
	virtual void update(float deltaTime);
	virtual void render();

	void reload(); 
	bool fire();

	/* Getters */
	inline FWeaponInfo getWeaponInfo() { return weaponInfo; }

protected:
	Model* weaponMesh;
	FWeaponInfo weaponInfo;

private:
	float canFire = 0;
	irrklang::ISoundEngine* soundEngine;
	void prepareMuzzleFlash();
	void showMuzzleFlash();
};

#endif // !WEAPON_H
