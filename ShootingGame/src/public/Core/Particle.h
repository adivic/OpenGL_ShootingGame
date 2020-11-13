#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>

struct FParticle {
	glm::vec3 Position;
	glm::vec3 Velocity;
	glm::vec4 Color;
	float LifeSpan;

	FParticle() : Position(0.f), Velocity(0.f), Color(1.f), LifeSpan(0.0f) {}
};

#endif // !PARTICLE_H
