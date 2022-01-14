/*********************************/
/*   THRESHOLD        (  //      */
/*   weapon            ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "weapon.hpp"

#include <iostream>

AWeapon::AWeapon(float const rg,
                 unsigned int const& dmg,
                 unsigned int const& mag,
                 double const& cd,
                 const char* s,
                 const char* r,
                 std::string const & nm)
    : range(rg), damage(dmg), max(mag), cooldown(cd), name(nm) {
    shot = LoadSound(s);
    reload = LoadSound(r);
    SetSoundVolume(shot, 0.3f);
    SetSoundVolume(reload, 0.3f);
    barrel = max;
}

AWeapon::~AWeapon() {}

void AWeapon::refill() {
    std::cout << "reload" << std::endl;
    PlaySound(reload);
    barrel = max;
}
