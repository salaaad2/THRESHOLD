#include "entity.hpp"

Entity::Entity(void)
{
    posX = GetRandomValue(0, SCREENWIDTH);
    posY = GetRandomValue(0, SCREENHEIGHT);
    if (static_cast<int>(posX) & 1) {
        direction = (Vector2){posX / 100, -posY / 100};
    } else {
        direction = (Vector2){-posX / 100, posY / 100};
    }
}

Entity::~Entity() {}
