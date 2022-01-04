/*********************************/
/*   THRESHOLD        (  //      */
/*   entity            ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "entity.hpp"

Entity::Entity(void) : hp(1)
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
