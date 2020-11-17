#pragma once

#include "Components/Actor.h"
#include <Texture.h>

/* A scene actor on the level used to render */
class House : public Actor {

private:
	Texture texture;
	Shader shader;
	unsigned int VAO;

public:
	House();
	House(glm::vec3 pos, FRotator rotation = FRotator(0), glm::vec3 size = glm::vec3(1.f));
	~House();

	virtual void init() override;
	virtual void render() override;

};
