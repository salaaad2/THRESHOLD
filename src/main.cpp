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
            }
            break ;
        }
        case (GAMEPLAY):
        {
            break ;
        }
        case (ENDING):
        {
            break ;
        }
    }
    BeginDrawing();

    ClearBackground(RAYWHITE);

    switch (gs) {
        case (TITLE):
        {
            DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
            break ;
        }
        case (GAMEPLAY):
        {
            game->start();
            break ;
        }
        case (ENDING):
        {
            DrawText("GOOD BYE SCREEN", 20, 20, 40, LIGHTGRAY);
            break ;
        }
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
