#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <raylib.h>

// FIXME: Unused class

typedef struct Projectile {
    int posX, posY;
    Vector2 dir;
    float radius;
    float damage;
} Projectile;

#endif /* PROJECTILE_H */
