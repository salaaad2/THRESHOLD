/*********************************/
/*   THRESHOLD        (  //      */
/*   weapon            ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "weapon.hpp"

#include <iostream>

Weapon::Weapon(float const & rg, unsigned int const & dmg, unsigned int const & mag, const char *s, const char *r) :
    range(rg), damage(dmg), max(mag)
{
    InitAudioDevice();
    shot = LoadSound(s);
    reload = LoadSound(r);
    SetSoundVolume(shot, 0.3f);
    SetSoundVolume(reload, 0.3f);
    barrel = max;
}

Weapon::~Weapon() {}

void Weapon::refill()
{
    std::cout << "reload" << std::endl;
    PlaySound(reload);
    barrel = max;
}

int Weapon::bang()
{
    if (barrel == 0)
    {
        return (1);
    } else {
        barrel--;
        std::cout << "BANG : " << barrel << "shots left" << std::endl;
        PlaySound(shot);
        return (0);
    }
}
