#include "wp_enemyslingshot.hpp"

#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "entity.hpp"
#include "gameplay.hpp"

wp_enemysling::wp_enemysling(const char* s, const char* r)
    : AWeapon(300.0f, 10, 1, 0.0, s, r, "sling") {}

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
        en.posX = 0;
        en.posY = 0;
        en.direction = (Vector2){1.0f, 1.0f};
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
