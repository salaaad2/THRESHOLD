#include "gameplay.hpp"

#include <iostream>


Game::~Game()
{
    delete enemies;
    delete player;
}

Game::Game(void)
{
    // nEnemies = GetRandomValue(5, 15);

    enemies = 3;

    enemies = new std::vector<Entity>(nEnemies);
    player = new Entity;
    player->posX = SCREENWIDTH / 2;
    player->posY = SCREENHEIGHT / 2;
    player->direction.x = 1;
    player->direction.y = 0;
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
    DrawCircleV((Vector2){player->posX, player->posY}, 10, GREEN);
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
    player->posX += player->direction.x;
    player->posY += player->direction.y;
}

void Game::getKeys() const
{
    if (IsKeyPressed(KEY_UP)) {
        player->direction.x = 0;
        player->direction.y = -2;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        player->direction.x = 0;
        player->direction.y = 2;
    }
    if (IsKeyPressed(KEY_LEFT)) {
        player->direction.x = -2;
        player->direction.y = 0;
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        player->direction.x = 2;
        player->direction.y = 0;
    }
}
