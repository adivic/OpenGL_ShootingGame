#pragma once
#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <glad/glad.h>
#include <vector>
#include "Core/Particle.h"
#include "Shader.h"
#include "Texture.h"

class ParticleEmitter {

private:
	unsigned int amount;
	std::vector<FParticle> particles;

	Shader shader;
	Texture texture;
	unsigned int VAO;

	// initialize buffer and vertex attributes
	void init();
	//returns the first particle index that's currently unused (life < 0) 
	unsigned int getFirstUnusedParticle();
	//respawn particle
	void respawnParticle(FParticle& particle, /*Actor &actor,*/ glm::vec3 offset = glm::vec3(0));

public:
	ParticleEmitter(Shader shader, Texture tex, unsigned int ammout);
	void update(float deltaTime, unsigned int newParticles, glm::vec3 offset);
	void render();
};

#endif // !PARTICLE_EMITTER_H
