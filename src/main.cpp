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
#include <raylib.h> // basic libs

#include <map>
#include <filesystem> // additional libs

gameState gs = TITLE;

std::map<int, std::string> pick;

int main(void) {
  initWindow();
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "WIP -- muchashooter THRESHOLD");
  auto nPick = 0;

  Game* game = nullptr;

    std::string path = "../meta/maps";
    int i = 0;
    for (const auto & entry : std::filesystem::directory_iterator(path)) { // c++17 lol
        if (entry.path().filename().generic_string().find("start") != std::string::npos)
        {
            pick[i] = entry.path().filename().generic_string();
            i++;
        }
    }
  // Main game loop
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
                std::string s(path);
                s += "/";
                s += pick[nPick];
                game = new Game(s);
                gs = GAMEPLAY;
                game->start();
            }
            if (IsKeyPressed(KEY_DOWN) && nPick < (pick.size() - 1))
            {
                nPick++;
            }
            if (IsKeyPressed(KEY_UP) && nPick > 0)
            {
                nPick--;
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
            DrawText("THRESHOLD", 260, 160, 30, RAYWHITE);
            DrawRectangle(300, 200, 1000, 500, RAYWHITE);
            DrawText("PRESS ENTER", (SCREENWIDTH / 2) - 140, (SCREENHEIGHT / 2) + 50, 40, MAROON);
            break ;
        }
        case (PICK):
        {
            DrawRectangle(200, 100, 1200, 700, RAYWHITE);
            DrawRectangle(250, 150, 1100, 600, COOLPURPLE);
            DrawRectangle(300, 200, 1000, 500, RAYWHITE);
            DrawText("THRESHOLD", 260, 160, 30, RAYWHITE);

            DrawRectangle(350, 240 + (nPick * 40), 900, 50, PURPLE);
            for (auto n = 0 ; n < pick.size(); n++)
            {
                DrawText(pick[n].c_str(), 400,
                        240 + (n * 40), 40, COOLPURPLE);
            }
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
