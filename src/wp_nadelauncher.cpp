#include "wp_nadelauncher.hpp"

#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "entity.hpp"
#include "projectile.hpp"

wp_nadelauncher::wp_nadelauncher(const char* s, const char* r)
    : AWeapon(300.0f, 1, 30, 0.0, s, r, "nade", true) {}
wp_nadelauncher::~wp_nadelauncher() {}

int wp_nadelauncher::bang(std::vector<Entity>* enemies, Entity* player) {
    if (barrel == 0) {
        return (1);
    } else {
        Projectile* proj = new Projectile();
        proj->dir = player->direction;
        proj->radius = player->radius;
        proj->posX = player->posX;
        proj->posY = player->posY;

        barrel--;
        PlaySound(shot);
        t = GetTime();
        // here
        //
        //
        // there
        if (barrel == 0) {
            empty = true;
        }
        return (0);
    }
}

Projectile const& wp_nadelauncher::getProjectile() const {
    return (projectile);
}
