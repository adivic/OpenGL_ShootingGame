#include "Level.h"
#include "ResourceManager.h"
#include "Pawn.h"
#include <stb_image\stb_image.h>

Level::Level(unsigned int width, unsigned int height, Pawn* playerPawn)
    : Width(width), Height(height), player(playerPawn) {}

void Level::init() {

    for (unsigned int i = 0; i < 3; i++) {
        glm::vec3 pos;
        if (i == 0)
            pos = glm::vec3(-3.0f, 0.5051f, -3.0f);
        if(i == 1)
            pos = glm::vec3(-5.0f, 0.501f, 2.0f);
        if (i == 2)
            pos = glm::vec3(5.0f, 0.501f, -4.0f);
        auto h = std::make_unique<House>(House(pos, FRotator(0), glm::vec3(2.f)));
        houses.push_back((std::move(h)));
    }

    /* FLOOR */
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
    glGenVertexArrays(1, &floorVAO);
    glGenBuffers(1, &floorVBO);
    glBindVertexArray(floorVAO);
    glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    ResourceManager::getShader("Texture").use().setUniform1i("texture1", 0);
    glBindVertexArray(0);

    for (unsigned int i = 0; i < houses.size(); i++)
        houses[i]->init();
}

void Level::render() {
    Shader shader = ResourceManager::getShader("Texture");
    shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(player->getPlayerCamera()->fov), (float)Width / (float)Height, 0.1f, 100.f);
    shader.setUnifromMat4f("view", player->getPlayerCamera()->getViewMatrix());
    shader.setUnifromMat4f("projection", projection);
   
    for (unsigned int i = 0; i < houses.size(); i++)
        houses[i]->render();
    
    //Floor
    glBindVertexArray(floorVAO);
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::getTexture("Floor").bind();
    model = glm::mat4(1.f);
    model = glm::scale(model, glm::vec3(5.f, 1.f, 5.f));
    shader.setUnifromMat4f("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
