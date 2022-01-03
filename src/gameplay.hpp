#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "window.hpp"

#include <vector>

class Enemy {
    public:
        float posX;
        float posY;
        Vector2 direction;
        Enemy();
        ~Enemy();
};

class Game {
    int nEnemies;

    std::vector<Enemy> * enemies;

    public:
        Game();
        ~Game();

        void start() const ;
};

#endif // GAMEPLAY_H_
