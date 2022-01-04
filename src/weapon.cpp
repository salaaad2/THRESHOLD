/*********************************/
/*   THRESHOLD        (  //      */
/*   weapon            ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "weapon.hpp"

Weapon::Weapon(float const & rg, unsigned int const & dmg) :
    range(rg), damage(dmg)
{}

Weapon::~Weapon() {}
