#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "window.hpp"
#include "entity.hpp"

#include <vector>

class Game {
    int nEnemies;

    std::vector<Entity> * enemies;

    Entity * player;

    public:
        Game();
        ~Game();

        void start() const ;
        void draw() const ;
        int tick() const ;
        int getKeys() const ;
};

#endif // GAMEPLAY_H_
