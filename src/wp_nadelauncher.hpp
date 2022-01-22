/*********************************/
/*   THRESHOLD        (  //      */
/*   rifle             ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#ifndef WP_NADELAUNCHER_H_
#define WP_NADELAUNCHER_H_

#include "weapon.hpp"

class wp_nadelauncher : public AWeapon {
   public:
    wp_nadelauncher(const char* s, const char* r);
    ~wp_nadelauncher();

    int bang(std::vector<Entity>* enemies, Entity* player);
    Projectile const& getProjectile() const;
};

#endif
