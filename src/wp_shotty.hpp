/*********************************/
/*   THRESHOLD        (  //      */
/*   shotty            ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#ifndef WP_SHOTTY_H_
#define WP_SHOTTY_H_

#include "weapon.hpp"

class wp_shotty : public AWeapon {
   public:
    wp_shotty(const char* s, const char* r);
    ~wp_shotty();

    int bang(std::vector<Entity>* enemies, Entity* player);
};

#endif
