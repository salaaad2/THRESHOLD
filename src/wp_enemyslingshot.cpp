#include "wp_enemyslingshot.hpp"

#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "gameplay.hpp"
#include "entity.hpp"

wp_enemysling::wp_enemysling(const char* s, const char* r)
    : AWeapon(300.0f, 10, 2, 0.0, s, r) {}

int wp_enemysling::bang(std::vector<Entity>* enemies, Entity* baddie) {
    if (barrel == 0) {
        return (1);
    } else {
        barrel--;
        PlaySound(shot);
        t = GetTime();
        // enemysling spawns a new enemy every @reload seconds. thats it.
        // it's a slingshot
        //
        Entity en(1);
        en.posX = (baddie->posX += range);
        en.posY = (baddie->posY += range);
        en.direction = baddie->direction;
        en.radius = 20;
        en.currentWeapon = nullptr;
        en.idleTex = LoadTexture(SBIRE_TEX_IDLE);
        en.hurtTex = LoadTexture(SBIRE_TEX_HURT);
        enemies->push_back(en);
        std::cout << "push back enemy. so far so good " << std::endl;

        //
        // there
        if (barrel == 0) {
            empty = true;
        }
        return (0);
    }
}
