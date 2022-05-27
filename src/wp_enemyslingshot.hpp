/*********************************/
/*   THRESHOLD        (  //      */
/*   enemysling        ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#ifndef WP_ENEMYSLING_H_
#define WP_ENEMYSLING_H_

#include "weapon.hpp"

class wp_enemysling : public AWeapon {
   public:
    wp_enemysling(const char* s, const char* r);
    virtual ~wp_enemysling();

    int bang(std::vector<Entity>* enemies, Entity* player);
    Projectile const& getProjectile() const;
};

#endif
