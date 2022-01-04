/*********************************/
/*   THRESHOLD        (  //      */
/*   weaponh           ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#ifndef WEAPON_H_
#define WEAPON_H_

class Weapon {
    public:
        float const & range;
        unsigned int const & damage;
        Weapon(float const & rg, unsigned int const & dmg);
        ~Weapon();
};

#endif // WEAPON_H_
