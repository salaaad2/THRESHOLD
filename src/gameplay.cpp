/*********************************/
/*   THRESHOLD        (  //      */
/*   gameplay          ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "gameplay.hpp"

#include <raylib.h>
#include <fstream>
#include <iostream>
#include <string>
#include "raymath.h"

#include "weapon.hpp"
#include "window.hpp"
#include "wp_assaultrifle.hpp"
#include "wp_enemyslingshot.hpp"
#include "wp_shotty.hpp"

Game::Game(std::string const& path) : current(path) {
    std::ifstream ifs(path);
    std::string tok;
    auto radius = 0;
    auto ehp = 0;

    std::cout << "Init: reading map file [" << path << "]" << std::endl;
    while (ifs >> tok) {
        if (tok == "ENEMIES") {
            ifs >> tok;
            std::cout << "will spawn " << tok << " enemies";
            nEnemies = std::atoi(tok.c_str());
            ifs >> tok;
            radius = std::atoi(tok.c_str());
        }
        if (tok == "NEXT") {
            ifs >> tok;
            next = tok;
            std::cout << "next level is " << next;
        }
        if (tok == "BOSS") {
            ifs >> tok;
            ehp = (tok == "0") ? 1 : 0;
            if (ehp == 0) {
                ifs >> tok;
                ehp = std::atoi(tok.c_str());
            }
        }
        if (tok == "WAVES") {
            ifs >> tok;
            nWaves = std::atoi(tok.c_str());
            ifs >> tok;
            nPerWave = std::atoi(tok.c_str());
        }
        if (tok == "BACKGROUND") {
            ifs >> tok;
            background = tok;
        }
    }
    ifs.close();
    enemies = new std::vector<Entity>;
    InitAudioDevice();

    AWeapon* shotty = new wp_shotty(SHOTTY_BANG, SHOTTY_RELOAD);
    AWeapon* ar = new wp_assaultrifle(AR_BANG,
                                      SHOTTY_RELOAD
    );
    AWeapon* sling = new wp_enemysling(SHOTTY_BANG, SHOTTY_RELOAD);

    for (auto i = 0; i < nPerWave; i++) {
        if (ehp == 1) {
            Entity en(ehp);
            en.radius = radius;
            en.idleTex = LoadTexture(SBIRE_TEX_IDLE);
            en.hurtTex = LoadTexture(SBIRE_TEX_HURT);
            en.currentWeapon = nullptr;
            enemies->push_back(en);
        } else {
            Entity en(ehp);
            en.radius = radius;
            en.wp[0] = sling;
            en.currentWeapon = en.wp[0];
            en.idleTex = LoadTexture(BOSS_TEX_IDLE);
            en.hurtTex = LoadTexture(BOSS_TEX_HURT);
            enemies->push_back(en);  // legacy code. TODO: remove AKchually no
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

    crosshair = LoadTexture(CROSSHAIR_TEX);

    player->wp[0] = shotty;
    player->wp[1] = ar;
    player->currentWeapon = player->wp[0];
    player->idleTex = LoadTexture(MUCHACHO_TEX);
}

Game::~Game() {
    delete enemies;
    delete player;
}

void Game::start() {
    std::cout << "----- Gameplay: Start -----" << std::endl;
    std::cout << "Gameplay: " << nEnemies << "enemies need to be spawned"
              << std::endl;
    frameWidth = player->idleTex.width;
    frameHeight = player->idleTex.height;

    sourceRec = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight};

    origin = {(float)frameWidth, (float)frameHeight};
}

// draw bad boys and player
void Game::draw() {
    auto left = std::to_string(enemies->size());

    for (auto& en : *enemies) {
        if (en.hp == 0)
            DrawTextureEx(en.hurtTex,
                          (Vector2){en.posX - en.radius, en.posY - en.radius},
                          1.0f, 0.6f, WHITE);
        else {
            DrawTextureEx(en.idleTex,
                          (Vector2){en.posX - en.radius, en.posY - en.radius},
                          1.0f, 0.6f, WHITE);
        }
    }
    // Destination rectangle
    Rectangle destRec = {player->posX, player->posY, frameWidth * 1.8f,
                         frameHeight * 1.8f};

    // Origin of the texture (rotation/scale point), it's relative to
    // destination rectangle size
    DrawTexturePro(player->idleTex, sourceRec, destRec, origin,
                   Vector2Angle((Vector2){0.0f, 0.0f}, player->direction),
                   WHITE);

    DrawText("Enemies left : ", 10, 10, 20, GREEN);
    DrawText(left.c_str(), 150, 10, 20, RED);
    if (player->fury >= 5) {
        DrawText("[E] FURY", SCREENWIDTH - 300, 10, 50, RED);
    }
    for (auto i = 0; i < player->currentWeapon->barrel; i++) { // draw weapon ammo
        DrawRectangle(40 + (i * 20), SCREENHEIGHT - 60, 10, 30, RED);
    }
    if (enemies->at(0).hp >= 2) { // draw hp in boss stages
        for (auto i = 0; i < enemies->size(); i++) {
            for (auto j = 0; j < enemies->at(i).hp; j++) {
                DrawRectangle(400 + (j * 40), 80 + (i * 40), 40, 30,
                              COOLPURPLE);
            }
        }
    }
}

// progress the game & check for player death
// NEW: go towards player NEXT: spawn at different furyTimes
int Game::tick() {
    auto target = GetMousePosition();

    DrawTexture(crosshair, target.x, target.y, WHITE);

    auto v2 = (Vector2){target.x - player->posX, target.y - player->posY};

    DrawText(std::to_string(v2.x).c_str(), 1400, 10, 20, RED);
    DrawText(std::to_string(v2.y).c_str(), 1400, 30, 20, RED);

    player->direction = v2;

    if (player->victims == nPerWave && nWaves > 1) {
        nWaves--;
        for (int i = 0; i < nPerWave; i++) {
            Entity en(1);
            en.radius = 20;
            en.idleTex = LoadTexture(SBIRE_TEX_IDLE);
            en.hurtTex = LoadTexture(SBIRE_TEX_HURT);
            en.currentWeapon = nullptr;
            enemies->push_back(en);
        }
    }

    for (auto en = enemies->begin(); en != enemies->end(); en++) {
        if (en->hp > 0) {
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
            if ((GetRandomValue(0, 100) == 50) && (en->currentWeapon !=
            nullptr)) {
                std::cout << "spawn enemy" << std::endl;
                en->currentWeapon->bang(enemies, &(*en));
            }
        } else {
            if (en->posX >= SCREENWIDTH || en->posX <= 0 ||
                en->posY >= SCREENHEIGHT) {
                enemies->erase(en);
                return (0);
            }
        }

        en->posX += en->direction.x;  // zoning better
        en->posY += en->direction.y;
        if (en->hp != 0 &&  // check for player death (one shot one kill)
            CheckCollisionCircles((Vector2){player->posX, player->posY}, 10,
                                  (Vector2){en->posX, en->posY}, 40)) {
            return (1);
        }
    }
    return (0);
}

int Game::getKeys() {
    auto oldX = 0, oldY = 0,
         speed = 7;  // get position before processing keys to check
                     // for player movement in threshold mode
    oldX = player->posX;
    oldY = player->posY;
    if (IsKeyDown(KEY_W)) {
        player->posX += 0;
        if ((player->posY + speed) < 0)
            player->posY = 0;
        else
            player->posY += -speed;
    }
    if (IsKeyDown(KEY_S)) {
        player->posX += 0;
        if ((player->posY + speed) > SCREENHEIGHT)
            player->posY = SCREENHEIGHT;
        else
            player->posY += speed;
    }
    if (IsKeyDown(KEY_A)) {
        if ((player->posX - speed) < 0)  // avoid leaving the map
            player->posX = 0;
        else
            player->posX += -speed;
        player->posY += 0;
    }
    if (IsKeyDown(KEY_D)) {
        if ((player->posX + speed) > SCREENWIDTH)
            player->posX = SCREENWIDTH;
        else
            player->posX += speed;
        player->posY += 0;
    }
    if (player->fury >= 5 && IsKeyDown(KEY_E)) {
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
    if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (shoot()) {
            return (0);
        }
        if (player->victims == nEnemies) {
            return (2);
        }
    }
    if (player->threshold) {
        if (GetTime() >= (player->furyTime + 5)) {
            player->fury = 0;
            player->threshold = false;
        }
        if (oldX != player->posX || oldY != player->posY) {
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
        if (GetTime() >= (player->reloadTime + 2)) {
            player->currentWeapon->refill();
            player->currentWeapon->empty = false;
        }
    }
    return (0);
}

int Game::shoot() const {
    if (player->currentWeapon->empty == true) {
        return (0);
    }
    player->currentWeapon->bang(enemies, player);
    if (player->currentWeapon->empty == true) {
        player->reloadTime = GetTime();
    }
    return (0);
}

std::string const& Game::getNext() const {
    return next;
}

std::string const& Game::getCurrent() const {
    return current;
}

std::string const& Game::getBackground() const {
    return background;
}

int const& Game::getKills() const {
    return player->victims;
}
