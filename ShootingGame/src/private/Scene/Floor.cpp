#include "Scene/Floor.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ResourceManager.h>

Floor::Floor() : Actor() {
    position = glm::vec3(1.f, 1.001f, 2.f);
    size = glm::vec3(3.f);
}

Floor::Floor(glm::vec3 pos, FRotator rot, glm::vec3 modelSize)
    : Actor(pos, rot, size) {

    position = pos;
    rotation = rot;
    size = modelSize;
}

Floor::~Floor() {}

void Floor::init() {
    float planeVertices[] = {
        // positions          // texture Coords 
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
    unsigned int floorVBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &floorVBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    ResourceManager::getShader("Texture").use().setUniform1i("texture1", 0);
    glBindVertexArray(0);
}   

void Floor::render() {
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::getTexture("Floor").bind();
    glm::mat4 model = glm::mat4(1.f);
    model = glm::scale(model, size);
    shader.setUnifromMat4f("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
