/*********************************/
/*   THRESHOLD        (  //      */
/*   entityh           ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#ifndef ENEMY_H_
#define ENEMY_H_

#include "window.hpp"

#include "weapon.hpp"

class Entity {
    public:
        int hp;
        float posX;
        float posY;
        Vector2 direction;
        Weapon * wp;
        Entity();
        ~Entity();
};

#endif // ENEMY_H_
