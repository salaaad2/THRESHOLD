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
        wp_shotty(float const &rg, unsigned int const &dmg, unsigned int const & mag, const char *s, const char *r);
        ~wp_shotty();

        int bang(std::vector<Entity> * enemies, Vector2 playerDirection, Vector2 playerPosition) ;
};


#endif
