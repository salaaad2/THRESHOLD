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

Game* game = new Game("../meta/maps/stage_1_start.bfm");

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
        case (NEXT):
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                gs = TITLE;
                std::string next("../meta/maps/");
                next += game->getNext();

                delete game;
                CloseAudioDevice();
                if (game->getNext() != "0") {
                    game = new Game(next);
                }
            }
            break ;
        }
        case (ENDING):
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                gs = TITLE;
                auto next = game->getNext();
                delete game;
                CloseAudioDevice();
                if (next != "0") {
                    game = new Game("../meta/maps/stage_1_start.bfm");
                }
            }
            break ;
        }
    }
    BeginDrawing();

    ClearBackground(COOLPURPLE);

    switch (gs) {
        case (TITLE):
        {
            DrawCircle(SCREENWIDTH / 2, SCREENHEIGHT / 2, 200, BLACK);
            DrawText("THRESHOLD", (SCREENWIDTH / 2) - 140, SCREENHEIGHT / 2, 40, RED);
            DrawText("PRESS ENTER", (SCREENWIDTH / 2) - 140, (SCREENHEIGHT / 2) + 50, 40, MAROON);
            break ;
        }
        case (GAMEPLAY):
        {
            if (auto code = game->getKeys()) {
                if (code == 1)
                {gs = ENDING;}
                else if (code == 2)
                {gs = NEXT;}
            }
            game->draw();
            break ;
        }
        case (NEXT):
        {
            ClearBackground(COOLPURPLE);
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
