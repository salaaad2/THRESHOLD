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

  float const &range;
  unsigned int const &damage;

public:
  Weapon(float const &rg, unsigned int const &dmg, const char *s, const char *r);
  ~Weapon();

  void bang() const ;
};

#endif // WEAPON_H_
