#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "window.hpp"

class Enemy {
    float posX;
    float posY;
    Vector2 direction;
    public:
        Enemy();
        ~Enemy();
};

class Game {
    int nEnemies;

    Enemy * enemies;

    public:
        Game();
        ~Game();

        void start() const ;
};

#endif // GAMEPLAY_H_
