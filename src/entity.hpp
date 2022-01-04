#ifndef ENEMY_H_
#define ENEMY_H_

#include "window.hpp"

class Entity {
    public:
        int hp;
        float posX;
        float posY;
        Vector2 direction;
        Entity();
        ~Entity();
};

#endif // ENEMY_H_
