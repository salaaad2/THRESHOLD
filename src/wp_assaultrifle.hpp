/*********************************/
/*   THRESHOLD        (  //      */
/*   rifle             ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#ifndef WP_ASSAULTRIFLE_H_
#define WP_ASSAULTRIFLE_H_

#include "weapon.hpp"

class wp_assaultrifle : public AWeapon {
    public:
        wp_assaultrifle(const char *s, const char *r);
        ~wp_assaultrifle();

        int bang(std::vector<Entity> * enemies, Vector2 playerDirection, Vector2 playerPosition, int * victims) ;
};


#endif
