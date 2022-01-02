#ifndef WINDOW_H_
#define WINDOW_H_

#include "raylib.h"

int initWindow(void);

#define SCREENWIDTH  800
#define SCREENHEIGHT 450

typedef enum gameState {
TITLE = 0, GAMEPLAY, ENDING
} gameState ;

#endif // WINDOW_H_
