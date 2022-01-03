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

class Player {
    public:
        float posX;
        float posY;
        Vector2 direction;
        Player();
        ~Player();
};

class Game {
    int nEnemies;

    std::vector<Enemy> * enemies;

    public:
        Game();
        ~Game();

        void start() const ;
        void draw() const ;
        void tick() const ;
        void getKeys() const ;
};

#endif // GAMEPLAY_H_
