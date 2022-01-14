#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <raylib.h>

class Projectile {
    Vector2 const& direction;
    Vector2 const& position;

   public:
    Projectile(Vector2 const& direction, Vector2 const& position);
    ~Projectile();
};

#endif /* PROJECTILE_H */
