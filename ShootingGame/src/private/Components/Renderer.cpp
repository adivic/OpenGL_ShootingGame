#include "Components/Renderer.h"
#include "ResourceManager.h"
#include <iostream>
#include "Pawn.h"

Renderer::Renderer(unsigned int width, unsigned int height, Pawn* pawn) 
	: Width(width), Height(height), player(pawn) {}

Renderer::~Renderer() {}

void Renderer::init() {
	float vertices[] = { 
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	//float offset = 1.0f / 300.0f;
	//float offsets[9][2] = {
	//	{ -offset,  offset  },  // top-left
	//	{  0.0f,    offset  },  // top-center
	//	{  offset,  offset  },  // top-right
	//	{ -offset,  0.0f    },  // center-left
	//	{  0.0f,    0.0f    },  // center-center
	//	{  offset,  0.0f    },  // center - right
	//	{ -offset, -offset  },  // bottom-left
	//	{  0.0f,   -offset  },  // bottom-center
	//	{  offset, -offset  }   // bottom-right    
	//};
	unsigned int vbo;
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	Shader shader = ResourceManager::getShader("ScreenTexture");
	shader.use().setUniform1i("screenTexture", 0);
	shader.setUniform1f("time", glfwGetTime());
	//glUniform2fv(glGetUniformLocation(shader.ID, "offsets"), 9, (float*)offsets);
	//float blur_kernel[9] = {
	//	1.0f / 32.f, 2.0f / 32.0f, 1.0f / 32.0f,
	//	2.0f / 32.f, 4.0f / 32.0f, 2.0f / 32.0f,
	//	1.0f / 32.f, 2.0f / 32.0f, 1.0f / 32.0f
	//};
	//glUniform1fv(glGetUniformLocation(shader.ID, "blur_kernel"), 9, blur_kernel);

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);

	/* Renderbuffer */
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "[ERROR RENDERER]: Framebuffer is not complete!\n";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::update() {}

void Renderer::renderBegin() {
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glClearColor(.1f, .1f, .1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::renderEnd() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(.1f, .1f, .1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	Shader shader = ResourceManager::getShader("ScreenTexture");
	shader.use();
	shader.setUniform1i("bShake", player->getWeapon()->isFiring());
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
