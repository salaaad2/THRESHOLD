#include "gameplay.hpp"

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
    nEnemies = GetRandomValue(0, 15);

    enemies = new Enemy[15];
}

void Game::start() const
{

}
