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
#include <filesystem>
#include <raylib.h>

gameState gs = TITLE;


int main(void) {
  initWindow();

  // Main game loop
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "WIP -- coolspace");
  Game* game = nullptr;
  while (!WindowShouldClose()) /* Detect window close button or ESC key */
  {
    switch (gs) {
        case (TITLE):
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                gs = PICK;
            }
            break ;
        }
        case (PICK):
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                gs = GAMEPLAY;
                game->start();
            }
            if (IsKeyPressed(KEY_DOWN))
            {
                // pick++
            }
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
                auto current = game->getCurrent();
                delete game;
                CloseAudioDevice();
                game = new Game(current);
            }
            break ;
        }
    }
    BeginDrawing();

    ClearBackground(COOLPURPLE);

    switch (gs) {
        case (TITLE):
        {
            DrawRectangle(200, 100, 1200, 700, RAYWHITE);
            DrawRectangle(250, 150, 1100, 600, COOLPURPLE);
            DrawRectangle(300, 200, 1000, 500, RAYWHITE);
            DrawText("THRESHOLD", 260, 160, 30, RAYWHITE);
            DrawText("PRESS ENTER", (SCREENWIDTH / 2) - 140, (SCREENHEIGHT / 2) + 50, 40, MAROON);
            break ;
        }
        case (PICK):
        {
            std::string path = "../meta/maps";
            int i = 0;
            DrawRectangle(200, 100, 1200, 700, RAYWHITE);
            DrawRectangle(250, 150, 1100, 600, COOLPURPLE);
            DrawRectangle(300, 200, 1000, 500, RAYWHITE);
            for (const auto & entry : std::filesystem::directory_iterator(path)) {
                DrawText("TEST", SCREENWIDTH / 2, (SCREENHEIGHT / 2) + i * 40, 40, COOLPURPLE);
                i++;
            }
            DrawText("THRESHOLD", 260, 160, 30, RAYWHITE);
            break ;
        }
        case (GAMEPLAY):
        {
            if (auto code = game->getKeys()) {
                if (code == 1) // death
                {gs = ENDING;}
                else if (code == 2) // level end
                {gs = NEXT;}
            }
            game->draw();
            break ;
        }
        case (NEXT):
        {
            ClearBackground(COOLPURPLE);
            DrawCircle(SCREENWIDTH / 2, SCREENHEIGHT / 2, 200, BLACK);
            DrawText("STAGE CLEARED\nNEXT LEVEL :\n", (SCREENWIDTH / 2) - 200, (SCREENHEIGHT / 2) - 50, 40, WHITE);
            DrawText(game->getNext().c_str(), (SCREENWIDTH / 2) - 100, (SCREENHEIGHT / 2) + 50, 40, WHITE);
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
    EndMode2D();
  CloseWindow();
  return 0;
}
