#pragma once
#include "Components/Actor.h"
#include <Texture.h>

class Floor : public Actor {
private:
	Texture texture;
	Shader shader;
	unsigned int VAO;

public:
	Floor();
	Floor(glm::vec3 pos, FRotator rotation = FRotator(0), glm::vec3 size = glm::vec3(1.f));
	~Floor();

	virtual void init() override;
	virtual void render() override;
};