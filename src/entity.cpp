/*********************************/
/*   THRESHOLD        (  //      */
/*   entity            ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "entity.hpp"

Entity::Entity() : Entity(1) {}

Entity::Entity(int const& h) : hp(h) {
    auto dir = GetRandomValue(0, 3);

    switch (dir) {
        case (0): {
            posX =
                GetRandomValue((SCREENWIDTH / 2) - 30, (SCREENWIDTH / 2) + 30);
            posY = GetRandomValue(0, 40);
            break;
        }
        case (1): {
            posX = GetRandomValue(SCREENWIDTH - 20, SCREENWIDTH + 20);
            posY = GetRandomValue((SCREENHEIGHT / 2) - 30,
                                  (SCREENHEIGHT / 2) + 30);
            break;
        }
        case (2): {
            posX =
                GetRandomValue((SCREENWIDTH / 2) - 30, (SCREENWIDTH / 2) + 30);
            posY = GetRandomValue(SCREENHEIGHT - 20, SCREENHEIGHT + 20);
            break;
        }
        case (3): {
            posX = GetRandomValue(SCREENWIDTH - 20, SCREENWIDTH + 20);
            posY = GetRandomValue((SCREENHEIGHT / 2), (SCREENHEIGHT / 2) + 10);
            break;
        }
    }

    direction = (Vector2){0.02f, 0.0f};
    threshold = false;
}

Entity::~Entity() {}
