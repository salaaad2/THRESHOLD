#include "wp_shotty.hpp"

#include <iostream>

wp_shotty::wp_shotty(float const &rg, unsigned int const &dmg, unsigned int const & mag, const char *s, const char *r)
    : AWeapon(rg, dmg, mag, s, r)
{}



int wp_shotty::bang()
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
