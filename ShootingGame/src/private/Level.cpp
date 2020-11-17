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

    floor = std::make_unique<Floor>(Floor(glm::vec3(0), FRotator(0), glm::vec3(10.f, 1.f, 10.f)));

    for (unsigned int i = 0; i < houses.size(); i++)
        houses[i]->init();
    
    floor->init();
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
    
    floor->render();

}
