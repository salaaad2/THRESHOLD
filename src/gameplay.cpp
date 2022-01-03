#include "gameplay.hpp"

#include <iostream>


Enemy::Enemy(void)
{
    posX = GetRandomValue(0, SCREENWIDTH);
    posY = GetRandomValue(0, SCREENHEIGHT);
    direction = (Vector2){posX, posY};
}

Enemy::~Enemy() {}
Game::~Game() {}

Game::Game(void)
{
    nEnemies = GetRandomValue(5, 15);

    enemies = new std::vector<Enemy>(nEnemies);
}

void Game::start() const
{
    std::cout << "----- Gameplay: Start -----" << std::endl;
    std::cout << "Gameplay: " << nEnemies << "enemies need to be spawned" << std::endl;

    for (auto & en : *enemies)
    {
        DrawCircleV(en.direction, 10, RED);
    }

}
