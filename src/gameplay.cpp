/*********************************/
/*   THRESHOLD        (  //      */
/*   gameplay          ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "gameplay.hpp"

#include "raymath.h"
#include <fstream>

Game::Game(std::string const & path)
{
    std::ifstream ifs(path);
    std::string tok;

    std::cout << "Init: reading map file [" << path << "]" << std::endl;
    while (ifs >> tok)
    {
        if (tok == "E")
        {
            ifs >> tok;
            std::cout << "will spawn " << tok << " enemies" << std::endl;
            nEnemies = std::atoi(tok.c_str());
        }
    }
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
    auto left = std::to_string(nEnemies);
    for (auto & en : *enemies)
    {
        DrawCircleV((Vector2){en.posX, en.posY}, 10, RED);
    }
    DrawCircleV((Vector2){player->posX, player->posY}, 10, GREEN);
    DrawText("Enemies left : ", 10, 10, 20, GREEN);
    DrawText(left.c_str(), 150, 10, 20,RED);
}


int Game::tick() const
{
    for (auto & en : *enemies)
    {
        if (en.posX >= SCREENWIDTH || en.posX <= 0) {
          en.direction.x = -en.direction.x;
        }
        if (en.posY >= SCREENHEIGHT || en.posY <= 0) {
          en.direction.y = -en.direction.y;
        }
        en.posX += en.direction.x;
        en.posY += en.direction.y;
        if (CheckCollisionCircles((Vector2){player->posX, player->posY}, 10,
                                  (Vector2){en.posX, en.posY}, 10)) {
            std::cout << "you died" << std::endl;
            return (1);
        }
    }
    return (0);
}

int Game::getKeys() const
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
        for (auto en = enemies->begin(); en != enemies->end(); en++)
        {
            if (CheckCollisionPointLine((Vector2){en->posX, en->posY}, (Vector2){player->posX, player->posY}, Vector2Add((Vector2){player->posX, player->posY}, player->direction), 20))
            {
              std::cout << "hit enemy at " << en->posX << "|" << en->posY
                        << std::endl;
              enemies->erase(en);
              return (0);
            }
        }
        DrawLineEx((Vector2){player->posX, player->posY}, Vector2Add((Vector2){player->posX, player->posY}, player->direction), 20, RED);

    }
    if (oldX != player->posX ||
        oldY != player->posY)
    {
        if (this->tick()) {
            return (1);
        }
    }
    aimer.x = (player->direction.x / 3);
    aimer.y = (player->direction.y / 3);
    DrawLineEx((Vector2){player->posX, player->posY}, Vector2Add((Vector2){player->posX, player->posY}, aimer), 5, GREEN);
    return (0);
}
