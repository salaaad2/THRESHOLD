/*********************************/
/*   THRESHOLD        (  //      */
/*   window            ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "window.hpp"

int
initWindow(void) {
    // Initialization
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "WIP -- coolspace");
    SetTargetFPS(60);

    return (0);
}
