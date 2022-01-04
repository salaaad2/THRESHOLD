#include "gameplay.hpp"

#include <iostream>

#include "raymath.h"

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

Game::~Game()
{
    delete enemies;
    delete player;
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
}

void Game::getKeys() const
{
    auto oldX = 0, oldY = 0;
    auto aimer = player->direction;

    oldX = player->posX;
    oldY = player->posY;
    if (IsKeyDown(KEY_W)) {
        player->posX += 0;
        player->posY += -4;
    }
    if (IsKeyDown(KEY_S)) {
        player->posX += 0;
        player->posY += 4;
    }
    if (IsKeyDown(KEY_A)) {
        player->posX += -4;
        player->posY += 0;
    }
    if (IsKeyDown(KEY_D)) {
        player->posX += 4;
        player->posY += 0;
    }
    if (IsKeyDown(KEY_LEFT)) {
        player->direction = Vector2Rotate(player->direction, -0.1f); // left
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player->direction = Vector2Rotate(player->direction, 0.1f);
    }
    if (IsKeyPressed(KEY_SPACE)) {
        DrawLineEx((Vector2){player->posX, player->posY}, Vector2Add((Vector2){player->posX, player->posY}, player->direction), 20, RED);
    }
    if (oldX != player->posX || oldY != player->posY)
    {
        this->tick();
    }
    aimer.x = (player->direction.x / 3);
    aimer.y = (player->direction.y / 3);
    DrawLineEx((Vector2){player->posX, player->posY}, Vector2Add((Vector2){player->posX, player->posY}, aimer), 5, GREEN);
}
