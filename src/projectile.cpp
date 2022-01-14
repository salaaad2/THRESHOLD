#include "projectile.hpp"
#include <raylib.h>

Projectile::Projectile(Vector2 const& dir, Vector2 const& pos)
    : direction(dir), position(pos) {}

Projectile::~Projectile() {}

Projectile *
Projectile::getProjectile() {
    return (this);
}
