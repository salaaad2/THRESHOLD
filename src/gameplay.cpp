/*********************************/
/*   THRESHOLD        (  //      */
/*   gameplay          ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "gameplay.hpp"

#include "raymath.h"
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <string>

#include "weapon.hpp"
#include "window.hpp"
#include "wp_assaultrifle.hpp"
#include "wp_shotty.hpp"

Game::Game(std::string const & path) : current(path)
{
    std::ifstream ifs(path);
    std::string tok;
    auto radius = 0;
    auto ehp = 0;

    std::cout << "Init: reading map file [" << path << "]" << std::endl;
    while (ifs >> tok)
    {
        if (tok == "ENEMIES")
        {
            ifs >> tok;
            std::cout << "will spawn " << tok << " enemies";
            nEnemies = std::atoi(tok.c_str());
            ifs >> tok;
            radius = std::atoi(tok.c_str());
        }
        if (tok == "NEXT")
        {
            ifs >> tok;
            next = tok;
            std::cout << "next level is " << next;
        }
        if (tok == "BOSS")
        {
            ifs >> tok;
            ehp = (tok == "0") ? 1 : 0;
            if (ehp == 0) {
                ifs >> tok;
                ehp = std::atoi(tok.c_str());
            }
        }
        if (tok == "WAVES")
        {
            ifs >> tok;
            nWaves = std::atoi(tok.c_str());
            ifs >> tok;
            nPerWave = std::atoi(tok.c_str());
        }
    }
    ifs.close();
    enemies = new std::vector<Entity>;
    for (auto i = 0; i < nEnemies; i++) {
        if (ehp == 0) {
            Entity en(ehp);
        en.radius = radius;
            en.idleTex = LoadTexture(SBIRE_TEX_IDLE);
            en.hurtTex = LoadTexture(SBIRE_TEX_HURT);
            enemies->push_back(en);
        } else {
            Entity en(ehp);
        en.radius = radius;
            en.idleTex = LoadTexture(SBIRE_TEX_IDLE);
            en.hurtTex = LoadTexture(SBIRE_TEX_HURT);
            enemies->push_back(en); // legacy code. TODO: remove
        }
    }
    player = new Entity;
    player->posX = 0;
    player->posY = SCREENHEIGHT / 2.0f;
    player->direction.x = 100;
    player->direction.y = 0;
    player->radius = 10;
    player->victims = 0;
    player->fury = 0;
    InitAudioDevice();

    cam.target = (Vector2){player->posX, player->posY};
    cam.offset = (Vector2){SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;
    AWeapon * shotty = new wp_shotty(
            SHOTTY_BANG,
            SHOTTY_RELOAD
    );
    AWeapon * ar = new wp_assaultrifle(
        AR_BANG,
        SHOTTY_RELOAD // TODO: get sound
    );

    player->wp[0] = shotty;
    player->wp[1] = ar;
    player->currentWeapon = player->wp[0];
    player->idleTex = LoadTexture(MUCHACHO_TEX);
}

Game::~Game()
{
    delete enemies;
    delete player;
}

void Game::start()
{
    std::cout << "----- Gameplay: Start -----" << std::endl;
    std::cout << "Gameplay: " << nEnemies << "enemies need to be spawned" << std::endl;
    frameWidth = player->idleTex.width;
    frameHeight = player->idleTex.height;

    sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };

    origin = { (float)frameWidth, (float)frameHeight };
}

// draw bad boys and player
void Game::draw()
{
    auto left = std::to_string(enemies->size());

    cam.target.x = player->posX;
    EndMode2D();
    auto texSize = (enemies->at(0).radius / 40.0f);
    for (auto & en : *enemies)
    {
        DrawCircle(en.posX, en.posY, en.radius, GREEN);
        if (en.hp == 0)
            DrawTextureEx(en.hurtTex, (Vector2){en.posX - 20, en.posY - 20}, 1.0f, 0.6f, WHITE);
        else {
            DrawTextureEx(en.idleTex, (Vector2){en.posX - 20, en.posY - 20}, 1.0f, 0.6f, WHITE);
        }
    }
    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec = { player->posX, player->posY, frameWidth * 1.8f, frameHeight * 1.8f };

    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    DrawTexturePro(player->idleTex, sourceRec, destRec, origin, Vector2Angle((Vector2){0.0f, 0.0f}, player->direction), WHITE);

    DrawText("Enemies left : ", 10, 10, 20, GREEN);
    DrawText(left.c_str(), 150, 10, 20, RED);
    if (player->fury >= 5) {
        DrawText("[E] FURY", SCREENWIDTH - 300, 10, 50, RED);
    }
    for (auto i = 0; i < player->currentWeapon->barrel; i++) {
        DrawRectangle(40 + (i * 20), SCREENHEIGHT - 60, 10, 30, RED);
    }

}

int Game::getDiff(Vector2 pos, Vector2 tip, Vector2 target) const
{
    if(((tip.x-pos.x)*(target.y-pos.y)-(tip.y-pos.y)*(target.x-pos.x))<0)
        return -1;
    if(((tip.x-pos.x)*(target.y-pos.y)-(tip.y-pos.y)*(target.x-pos.x))>0)
        return 1;

    return 0;
}

// progress the game & check for player death
// NEW: go towards player NEXT: spawn at different furyTimes
int Game::tick() const
{
    auto target = GetMousePosition();

    DrawLine(player->posX, player->posY, target.x, target.y, RAYWHITE);


    auto v2 = (Vector2){target.x - player->posX, target.y - player->posY};

    DrawText(std::to_string(v2.x).c_str(), 1400, 10, 20, RED);
    DrawText(std::to_string(v2.y).c_str(), 1400, 30, 20, RED);

    player->direction = v2;

    for (auto  en = enemies->begin(); en != enemies->end(); en++)
    {
        if (en->hp > 0)
        {
            if (en->posX >= SCREENWIDTH || en->posX <= 0) {
                en->direction.x = -en->direction.x;
            }
            if (en->posY >= SCREENHEIGHT || en->posY <= 0) {
                en->direction.y = -en->direction.y;
            }
            if (en->posX >= player->posX) {
                en->posX -= 2.1f;
                en->direction.x -= 0.1f;
            }
            if (en->posY >= player->posY) {
                en->posY -= 2.1f;
                en->direction.y -= 0.1f;
            }
            if (en->posX <= player->posX) {
                en->posX += 2.1f;
                en->direction.x += 0.1f;
            }
            if (en->posY <= player->posY) {
                en->posY += 2.1f;
                en->direction.y += 0.1f;
            }
      } else {
            if (en->posX >= SCREENWIDTH || en->posX <= 0 || en->posY >= SCREENHEIGHT ) {
              enemies->erase(en);
              return (0);
            }
        }

      en->posX += en->direction.x; // zoning better
      en->posY += en->direction.y;
      if (en->hp != 0 && // check for player death (one shot one kill)
          CheckCollisionCircles((Vector2){player->posX, player->posY}, 10,
                                (Vector2){en->posX, en->posY}, 40)) {
            return (1);
        }
    }
    return (0);
}

int Game::getKeys() const
{
    auto oldX = 0, oldY = 0; // get position before processing keys to check for player movement
                             // in threshold mode
    oldX = player->posX;
    oldY = player->posY;
    if (IsKeyDown(KEY_W)) {
        player->posX += 0;
        player->posY += -7;
    }
    if (IsKeyDown(KEY_S)) {
        player->posX += 0;
        player->posY += 7;
    }
    if (IsKeyDown(KEY_A)) {
        player->posX += -7;
        player->posY += 0;
    }
    if (IsKeyDown(KEY_D)) {
        player->posX += 7;
        player->posY += 0;
    }
    if (player->fury >= 5 &&
        IsKeyDown(KEY_E)) {
        player->furyTime = GetTime();

        player->threshold = true;
        player->fury = 0;
    }
    if (IsKeyDown(KEY_ONE)) {
        player->currentWeapon = player->wp[0];
    }
    if (IsKeyDown(KEY_TWO)) {
        player->currentWeapon = player->wp[1];
    }
    if (IsKeyDown(KEY_LEFT)) {
        player->direction = Vector2Rotate(player->direction, -0.1f); // left
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player->direction = Vector2Rotate(player->direction, 0.1f);
    }
    if (IsKeyPressed(KEY_SPACE)) {
        std::cout << "key space";
        if (shoot()) {
            return (0);
        }
        if (player->victims == nEnemies) {
            return (2);
        }
    }
    if (player->threshold)
    {
        if (GetTime() >= (player->furyTime + 5))
        {
            player->fury = 0;
            player->threshold = false;
        }
        if (oldX != player->posX ||
            oldY != player->posY)
        {
            if (this->tick()) {
                return (1);
            }
        }
    } else {
        if (this->tick()) {
            return (1);
        }
    }
    if (player->currentWeapon->empty) {
        if (GetTime() >= (player->reloadTime + 2))
        {
            player->currentWeapon->refill();
            player->currentWeapon->empty = false;
        }
    }
    return (0);
}


int
Game::shoot() const
{

        if (player->currentWeapon->empty == true) {
            return (0);
        }
        player->currentWeapon->bang(enemies, player);
        if (player->currentWeapon->empty == true) {
            player->reloadTime = GetTime();
        }
        return (0);
}

std::string const &
Game::getNext() const
{return next;}

std::string const &
Game::getCurrent() const
{return current;}
