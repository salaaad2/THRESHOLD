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
                GetRandomValue((SCREENWIDTH / 2) - 300, (SCREENWIDTH / 2) + 300);
            posY = GetRandomValue(0, 40);
            break;
        }
        case (1): {
            posX = GetRandomValue(SCREENWIDTH - 200, SCREENWIDTH + 200);
            posY = GetRandomValue((SCREENHEIGHT / 2) - 300,
                                  (SCREENHEIGHT / 2) + 300);
            break;
        }
        case (2): {
            posX =
                GetRandomValue((SCREENWIDTH / 2) - 300, (SCREENWIDTH / 2) + 300);
            posY = GetRandomValue(SCREENHEIGHT - 200, SCREENHEIGHT + 200);
            break;
        }
        case (3): {
            posX = GetRandomValue(SCREENWIDTH - 200, SCREENWIDTH + 200);
            posY = GetRandomValue((SCREENHEIGHT / 2), (SCREENHEIGHT / 2) + 100);
            break;
        }
    }

    direction = (Vector2){0.02f, 0.0f};
    threshold = false;
}

Entity::~Entity() {}
