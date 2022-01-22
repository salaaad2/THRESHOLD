/*********************************/
/*   THRESHOLD        (  //      */
/*   weaponh           ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#ifndef WEAPON_H_
#define WEAPON_H_

#include "projectile.hpp"
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
    unsigned int const damage;
    const std::string name;

    Projectile projectile;

   public:
    AWeapon(float const rg,           // range
            unsigned int const& dmg,  // damage
            unsigned int const& mag,  // mag capacity
            double const& cooldown,   // duh
            const char* s,            // shot sound  path
            const char* r,            // reload sound path
            std::string const& nm,    // name
            bool const& hasProj);     // projectiles ? yea/nay
    ~AWeapon();

    virtual int bang(std::vector<Entity>* enemies, Entity* player) = 0;
    void refill();

    virtual Projectile const& getProjectile() const = 0;

    bool empty;
    unsigned int barrel;
    bool hasProjectiles;
};

#endif  // WEAPON_H_
