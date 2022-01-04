/*********************************/
/*   THRESHOLD        (  //      */
/*   windowh           ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#ifndef WINDOW_H_
#define WINDOW_H_

#include "raylib.h"

int initWindow(void);

#define SCREENWIDTH  1600
#define SCREENHEIGHT 900

typedef enum gameState {
TITLE = 0, GAMEPLAY, ENDING
} gameState ;

#endif // WINDOW_H_
