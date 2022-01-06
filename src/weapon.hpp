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

#include <vector>

class Entity;

class AWeapon {
protected:
  Sound shot;
  Sound reload;

  unsigned int max;


  float const &range;
  unsigned int const &damage;

public:
  AWeapon(float const &rg, unsigned int const &dmg, unsigned int const & mag, const char *s, const char *r);
  ~AWeapon();

  virtual int bang(std::vector<Entity> * enemies, Vector2 playerDirection, Vector2 playerPosition, int * victims) = 0;
  void refill();

  bool empty;
  unsigned int barrel;
};

#endif // WEAPON_H_
