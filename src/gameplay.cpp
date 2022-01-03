#include "gameplay.hpp"

#include <iostream>


Game::~Game()
{
    delete enemies;
    delete player;
}

Game::Game(void)
{
    nEnemies = GetRandomValue(5, 15);

    enemies = new std::vector<Entity>(nEnemies);
    player = new Entity;
}

void Game::start() const
{
    std::cout << "----- Gameplay: Start -----" << std::endl;
    std::cout << "Gameplay: " << nEnemies << "enemies need to be spawned" << std::endl;
}

void Game::draw() const
{
    for (auto & en : *enemies)
    {
        DrawCircleV((Vector2){en.posX, en.posY}, 10, RED);
    }
}


void Game::tick() const
{
    for (auto & en : *enemies)
    {
        if (en.posX >= SCREENWIDTH || en.posX <= 0)
        {
            en.direction.x = -en.direction.x;
        }
        if (en.posY >= SCREENHEIGHT || en.posY <= 0)
        {
            en.direction.y = -en.direction.y;
        }
        en.posX += en.direction.x;
        en.posY += en.direction.y;
    }
}

void Game::getKeys() const
{
}
