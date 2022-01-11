#include "wp_assaultrifle.hpp"

#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "entity.hpp"

wp_assaultrifle::wp_assaultrifle(const char* s, const char* r)
    : AWeapon(300.0f, 10, 30, 0.0, s, r) {}

int wp_assaultrifle::bang(std::vector<Entity>* enemies, Entity* player) {
    if (barrel == 0) {
        return (1);
    } else {
        Vector2 playerDirection = Vector2Normalize(player->direction);
        playerDirection.x *= range;
        playerDirection.y *= range;
        Vector2 playerPosition = (Vector2){player->posX, player->posY};
        Vector2 rot1 = Vector2Rotate(playerDirection, -0.2f);
        Vector2 rot2 = Vector2Rotate(playerDirection, 0.2f);

        Vector2 add1 = Vector2Add(playerPosition, rot1);
        Vector2 add2 = Vector2Add(playerPosition, rot2);

        Vector2 r;
        barrel--;
        PlaySound(shot);
        t = GetTime();
        // here
        //
        r = playerDirection;
        r.x *= 2;
        r.y *= 2;
        for (auto en = enemies->begin(); en != enemies->end(); en++) {
            if (CheckCollisionPointLine((Vector2){en->posX, en->posY},
                                        playerPosition, add1,
                                        (en->radius * 2)) ||
                CheckCollisionPointLine(
                    (Vector2){en->posX, en->posY}, playerPosition,
                    Vector2Add(playerPosition, r), (en->radius * 2)) ||
                CheckCollisionPointLine((Vector2){en->posX, en->posY},
                                        playerPosition, add2,
                                        (en->radius * 2))) {  // enemy hit
                std::cout << "hit" << std::endl;
                en->hp--;
                if (en->hp == 0) {
                    en->direction.x = (playerDirection.x / 2);
                    en->direction.y = (playerDirection.y / 2);
                    player->victims += 1;
                }
                player->fury += 1;
                break;
            }
        }
        // assaultrifle cone
        DrawLineEx(playerPosition, add1, 10, ORANGE);
        DrawLineEx(playerPosition, Vector2Add(playerPosition, r), 10, ORANGE);
        DrawLineEx(playerPosition, add2, 10, ORANGE);

        //
        // there
        if (barrel == 0) {
            empty = true;
        }
        return (0);
    }
}
