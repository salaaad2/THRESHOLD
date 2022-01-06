/*********************************/
/*   THRESHOLD        (  //      */
/*   weapon            ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "weapon.hpp"

#include <iostream>

AWeapon::AWeapon(float const & rg, unsigned int const & dmg, unsigned int const & mag, const char *s, const char *r) :
    range(rg), damage(dmg), max(mag)
{
    InitAudioDevice();
    shot = LoadSound(s);
    reload = LoadSound(r);
    SetSoundVolume(shot, 0.3f);
    SetSoundVolume(reload, 0.3f);
    barrel = max;
}

AWeapon::~AWeapon() {}

void AWeapon::refill()
{
    std::cout << "reload" << std::endl;
    PlaySound(reload);
    barrel = max;
}
