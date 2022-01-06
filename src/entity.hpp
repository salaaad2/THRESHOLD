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
        int radius;
        int victims;
        int fury;
        bool threshold;
        float posX;
        float posY;
        double furyTime;
        double reloadTime;
        Vector2 direction;
        Weapon * wp;
        Image img;
        Texture2D idleTex;
        Texture2D hurtTex;

        Entity();
        Entity(int const & h);
        ~Entity();
};

#endif // ENEMY_H_
