/*********************************/
/*   THRESHOLD        (  //      */
/*   main              ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/


#include "window.hpp"
#include "gameplay.hpp"
#include <iostream>

gameState gs = TITLE;

Game* game = new Game;

int main(void) {
  initWindow();

  // Main game loop
  while (!WindowShouldClose()) /* Detect window close button or ESC key */
  {
    switch (gs) {
        case (TITLE):
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                gs = GAMEPLAY;
                game->start();
            }
            break ;
        }
        case (GAMEPLAY):
        {
            break ;
        }
        case (ENDING):
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                gs = TITLE;
            }
            break ;
        }
    }
    BeginDrawing();

    ClearBackground(RAYWHITE);

    switch (gs) {
        case (TITLE):
        {
            DrawText("THRESHOLD", (SCREENWIDTH / 2) - 150, SCREENHEIGHT / 2, 40, RED);
            DrawText("PRESS ENTER", (SCREENWIDTH / 2) - 150, (SCREENHEIGHT / 2) + 50, 40, MAROON);
            break ;
        }
        case (GAMEPLAY):
        {
            if (game->getKeys()) {
                gs = ENDING;
            }
            game->draw();
            break ;
        }
        case (ENDING):
        {
            DrawCircle(SCREENWIDTH / 2, SCREENHEIGHT / 2, 200, BLACK);
            DrawText("GOOD BYE", (SCREENWIDTH / 2) - 100, SCREENHEIGHT / 2, 40, WHITE);
            break ;
        }
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
