#include "gameplay.hpp"

#include <iostream>

#include "raymath.h"

Game::~Game()
{
    delete enemies;
    delete player;
}

Game::Game(void)
{
    // nEnemies = GetRandomValue(5, 15);

    nEnemies = 4;

    enemies = new std::vector<Entity>(nEnemies);
    player = new Entity;
    player->posX = SCREENWIDTH / 2;
    player->posY = SCREENHEIGHT / 2;
    player->direction.x = 100;
    player->direction.y = 100;
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
    // player->posX += player->direction.x;
    // player->posY += player->direction.y;
}

void Game::getKeys() const
{
    auto oldX = 0, oldY = 0;

    oldX = player->posX;
    oldY = player->posY;
    if (IsKeyDown(KEY_UP)) {
        player->posX += 0;
        player->posY += -4;
        player->direction = Vector2Rotate(player->direction, -0.1f);
    }
    if (IsKeyDown(KEY_DOWN)) {
        player->posX += 0;
        player->posY += 4;
        player->direction = Vector2Rotate(player->direction, 0.1f);
    }
    if (IsKeyDown(KEY_LEFT)) {
        player->posX += -4;
        player->posY += 0;
        player->direction = Vector2Rotate(player->direction, -0.1f);
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player->posX += 4;
        player->posY += 0;
        player->direction = Vector2Rotate(player->direction, 0.1f);
    }
    if (IsKeyDown(KEY_SPACE)) {
        DrawLineEx((Vector2){player->posX, player->posY}, Vector2Add((Vector2){player->posX, player->posY}, player->direction), 30, RED);
    }
    if (oldX != player->posX || oldY != player->posY)
    {
        this->tick();
    }
}
