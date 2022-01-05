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
    auto dir = GetRandomValue(0, 3);

    switch (dir)
    {
        case (0):
        {
            posX = GetRandomValue((SCREENWIDTH / 2) - 30, (SCREENWIDTH / 2) + 30);
            posY = 0;
            break;
        }
        case (1):
        {
            posX = SCREENWIDTH;
            posY = GetRandomValue((SCREENHEIGHT / 2) - 30, (SCREENHEIGHT / 2) + 30);
            break;
        }
        case (2):
        {
            posX = GetRandomValue((SCREENWIDTH / 2) - 30, (SCREENWIDTH / 2) + 30);
            posY = SCREENHEIGHT;
            break;
        }
        case (3):
        {
            posX = SCREENWIDTH;
            posY = GetRandomValue((SCREENHEIGHT / 2), (SCREENHEIGHT / 2) + 10);
            break;
        }
    }

    // if (static_cast<int>(posX) & 1) {
      direction = (Vector2){0.1f, 0.1f};
    // } else {
    //   direction = (Vector2){-posX / 100, posY / 100};
    // } // old pseudo-random path finder. now reworking so that they go towards the player
    radius = 10; // default radius. this is changed later
    threshold = false;
}

Entity::~Entity() {}
