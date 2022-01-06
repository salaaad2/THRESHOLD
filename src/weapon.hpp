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

class Weapon {
  Sound shot;
  Sound reload;

  unsigned int max;


  float const &range;
  unsigned int const &damage;

public:
  Weapon(float const &rg, unsigned int const &dmg, unsigned int const & mag, const char *s, const char *r);
  ~Weapon();

  int bang();
  void refill();

  bool empty;
  unsigned int barrel;
};

#endif // WEAPON_H_
