#include "wp_assaultrifle.hpp"

#include <iostream>
#include <raymath.h>
#include <raylib.h>

#include "entity.hpp"

wp_assaultrifle::wp_assaultrifle(const char *s, const char *r)
    : AWeapon(100, 10, 30, 0.0, s, r)
{}



int wp_assaultrifle::bang(std::vector<Entity> * enemies, Vector2 playerDirection, Vector2 playerPosition, int * victims)
{
    if (barrel == 0)
    {
        return (1);
    } else {
        barrel--;
        PlaySound(shot);
        // here
        //
        auto rot1 = Vector2Rotate(playerDirection, -0.2f);
        auto rot2 = Vector2Rotate(playerDirection, 0.2f);

        auto add1 = Vector2Add(playerPosition, rot1);
        auto add2 = Vector2Add(playerPosition, rot2);

        auto r = playerDirection;
        r.x *= 2;
        r.y *= 2;

        for (auto en = enemies->begin(); en != enemies->end(); en++)
        {
            if (CheckCollisionPointLine((Vector2){en->posX, en->posY}, playerPosition, add1, (en->radius * 2)) ||
                CheckCollisionPointLine((Vector2){en->posX, en->posY}, playerPosition, Vector2Add(playerPosition, r), (en->radius * 2)) ||
                CheckCollisionPointLine((Vector2){en->posX, en->posY}, playerPosition, add2, (en->radius * 2)))
            { // enemy hit
                std::cout << "hit" << std::endl;
                en->hp--;
                if (en->hp == 0)
                {
                    en->direction.x = (playerDirection.x / 2);
                    en->direction.y = (playerDirection.y / 2);
                }
                *victims += 1;
            }
        }
        // assaultrifle cone
        DrawLineEx(playerPosition, add1, 10, ORANGE);
        DrawLineEx(playerPosition,
                   Vector2Add(playerPosition,
                              r),
                   10, ORANGE);
        DrawLineEx(playerPosition, add2, 10, ORANGE);

        //
        // there
        if (barrel == 0)
        {
            empty = true;
        }
        return (0);
    }
}
