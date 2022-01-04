/*********************************/
/*   THRESHOLD        (  //      */
/*   weapon            ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "weapon.hpp"

Weapon::Weapon(float const & rg, unsigned int const & dmg, const char *s, const char *r) :
    range(rg), damage(dmg)
{
    InitAudioDevice();
    shot = LoadSound(s);
    reload = LoadSound(r);
    SetSoundVolume(shot, 0.3f);
    SetSoundVolume(reload, 0.3f);
}

Weapon::~Weapon() {}

void Weapon::bang() const
{
    PlaySound(shot);
}
