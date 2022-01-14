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

#include <iostream>
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
    const std::string name;

   public:
    AWeapon(float const rg,           // range
            unsigned int const& dmg,  // damage
            unsigned int const& mag,  // mag capacity
            double const& cooldown,   // duh
            const char* s,            // shot sound  path
            const char* r,            // reload sound path
            std::string const& nm);   // name
    ~AWeapon();

    virtual int bang(std::vector<Entity>* enemies, Entity* player) = 0;
    void refill();

    bool empty;
    unsigned int barrel;
};

#endif  // WEAPON_H_
