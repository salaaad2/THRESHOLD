/*********************************/
/*   THRESHOLD        (  //      */
/*   weaponh           ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#ifndef WEAPON_H_
#define WEAPON_H_

#include "raylib.h"

#include <vector>

class Entity;

class AWeapon {
   protected:
    Sound shot;
    Sound reload;

    unsigned int max;

    double cooldown;
    double t;

    float const range;
    unsigned int const& damage;

   public:
    AWeapon(float const rg,
            unsigned int const& dmg,
            unsigned int const& mag,
            double const& cooldown,
            const char* s,
            const char* r);
    ~AWeapon();

    virtual int bang(std::vector<Entity>* enemies, Entity* player) = 0;
    void refill();

    bool empty;
    unsigned int barrel;
};

#endif  // WEAPON_H_
