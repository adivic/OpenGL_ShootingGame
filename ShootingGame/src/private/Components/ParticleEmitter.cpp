#include "Components/ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(Shader pShader, Texture tex, unsigned int ammout) 
	: shader(pShader), texture(tex), amount(ammout) { 
	init();
}

void ParticleEmitter::init() {
	unsigned int VBO;
	float particle_quad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	//fill mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));

	//create amout default particle instances
	for(unsigned int i = 0; i < amount; i++)
		particles.push_back(FParticle());
}

unsigned int lastUsedParticle = 0;
unsigned int ParticleEmitter::getFirstUnusedParticle() {
	for (unsigned int i = lastUsedParticle; i < this->amount; ++i) {
		if (this->particles[i].LifeSpan <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// otherwise, do a linear search
	for (unsigned int i = 0; i < lastUsedParticle; ++i) {
		if (this->particles[i].LifeSpan <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// all particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
	lastUsedParticle = 0;
	
	return 0;
}

void ParticleEmitter::respawnParticle(FParticle& particle, glm::vec3 offset) {
	float random = ((rand() % 100) - 50) / 10.0f;
	float rColor = 0.5f + ((rand() % 100) / 100.0f);
	particle.Position = particle.Position + random + offset;
	particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
	particle.LifeSpan = 1.0f;
	particle.Velocity = particle.Velocity * 0.1f;

}

void ParticleEmitter::update(float deltaTime, unsigned int newParticles, glm::vec3 offset) {
	//add new particles
	for (unsigned int i = 0; i < newParticles; ++i) {
		int unusedParticles = getFirstUnusedParticle();
		respawnParticle(particles[unusedParticles], offset);
	}
	//update all particles
	for (unsigned int i = 0; i < amount; ++i) {
		FParticle& p = particles[i];
		p.LifeSpan -= deltaTime;
		if (p.LifeSpan > 0.f) {
			//particle is alive / update
			p.Position -= p.Velocity * deltaTime;
			p.Color.a -= deltaTime * 2.5f;
		}
	}
}

void ParticleEmitter::render() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader.use();
	for (FParticle p : particles) {
		if (p.LifeSpan > 0.f) {
			shader.setUniform3f("offset", p.Position);
			shader.setUniform4f("color", p.Color);
			texture.bind();
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
