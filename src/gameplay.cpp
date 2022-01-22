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
#include <memory>
#include <string>
#include "raymath.h"

#include "weapon.hpp"
#include "window.hpp"
#include "wp_assaultrifle.hpp"
#include "wp_enemyslingshot.hpp"
#include "wp_nadelauncher.hpp"
#include "wp_shotty.hpp"

Level* Game::parse(std::string const& path) {
    std::ifstream ifs(path);
    std::string tok;
    Level* ret = new Level();

    std::cout << "INIT: reading level.file [" << path << "]" << std::endl;
    while (ifs >> tok) {
        if (tok == "MINIONS") {
            ifs >> tok;
            ret->nMinion = std::atoi(tok.c_str());
            ifs >> tok;
            ret->mRadius = std::atoi(tok.c_str());
            ret->mHp = 1;
        }
        if (tok == "BOSS") {
            ifs >> tok;
            ret->nBoss = std::atoi(tok.c_str());
            ifs >> tok;
            ret->bHp = std::atoi(tok.c_str());
            ret->bRadius = 50;
            std::cerr << "DEBUG: bosses : " << ret->nBoss << "\n";
        }
        if (tok == "NEXT") {
            ifs >> tok;
            ret->next = tok;
            std::cout << "DEBUG: next level is " << ret->next;
        }
        if (tok == "WAVES") {
            ifs >> tok;
            ret->nWaves = std::atoi(tok.c_str());
            ifs >> tok;
            ret->nPerWave = std::atoi(tok.c_str());
        }
        if (tok == "BACKGROUND") {
            ifs >> tok;
            ret->background = tok;
        }
    }
    ret->nTotal = (ret->nBoss + ret->nGrunts + ret->nMinion);
    ret->current = path;
    ifs.close();
    return (ret);
}

Game::Game(std::string const& path) {
    auto radius = 0;
    auto ehp = 0;

    level = parse(path);

    enemies = new std::vector<Entity>;
    InitAudioDevice();

    AWeapon* shotty = new wp_shotty(SHOTTY_BANG, SHOTTY_RELOAD);
    AWeapon* ar = new wp_assaultrifle(AR_BANG, SHOTTY_RELOAD);
    AWeapon* nadelauncher = new wp_nadelauncher(AR_BANG, SHOTTY_RELOAD);
    AWeapon* sling = new wp_enemysling(SHOTTY_BANG, SHOTTY_RELOAD);

    for (auto i = 0; i < level->nMinion; i++) {
        Entity en(level->mHp);
        en.radius = level->mRadius;
        en.idleTex = LoadTexture(SBIRE_TEX_IDLE);
        en.hurtTex = LoadTexture(SBIRE_TEX_HURT);
        en.currentWeapon = nullptr;
        enemies->push_back(en);
    }
    for (auto i = 0; i < level->nBoss; i++) {
        Entity en(level->bHp);
        en.radius = level->bRadius;
        en.wp[0] = sling;
        en.currentWeapon = en.wp[0];
        en.idleTex = LoadTexture(BOSS_TEX_IDLE);
        en.hurtTex = LoadTexture(BOSS_TEX_HURT);
        enemies->push_back(en);  // legacy code. TODO: remove AKchually no
    }
    player = new Entity();
    player->posX = 0;
    player->posY = SCREENHEIGHT / 2.0f;
    player->direction.x = 100;
    player->direction.y = 0;
    player->radius = 10;
    player->victims = 0;
    player->fury = 0;
    player->wp[0] = shotty;
    player->wp[1] = ar;
    player->wp[2] = nadelauncher;
    player->currentWeapon = player->wp[0];
    player->idleTex = LoadTexture(MUCHACHO_TEX);

    crosshair = LoadTexture(CROSSHAIR_TEX);

    frameWidth = player->idleTex.width;
    frameHeight = player->idleTex.height;

    sourceRec = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight};

    origin = {(float)frameWidth, (float)frameHeight};
    nEnemies = level->nTotal;
}

Game::~Game() {
    delete enemies;
    delete player;
    delete level;
}

// draw bad boys and player
void Game::draw() {
    auto left = std::to_string(enemies->size());

    for (auto& en : *enemies) {
        if (en.hp <= 0)
            DrawTextureEx(en.hurtTex,
                          (Vector2){en.posX - en.radius, en.posY - en.radius},
                          1.0f, 0.6f, WHITE);
        else {
            DrawTextureEx(en.idleTex,
                          (Vector2){en.posX - en.radius, en.posY - en.radius},
                          1.0f, 0.6f, WHITE);
        }
        if (en.hp > 1) {
            for (auto j = 0; j < en.hp; j++) {
                DrawRectangle((en.posX - 50) + (10 * j), en.posY - 100, 10, 10,
                              COOLPURPLE);
            }
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
    for (auto i = 0; i < player->currentWeapon->barrel;
         i++) {  // draw weapon ammo
        DrawRectangle(40 + (i * 20), SCREENHEIGHT - 60, 10, 30, RED);
    }

    for (auto& pr : *projectiles) {
        DrawCircle(pr.posX, pr.posY, pr.radius, COOLPURPLE);
    }
}

// progress the game & check for player death
// NEW: go towards player NEXT: spawn at different furyTimes
int Game::tick() {
    // player logic
    //
    auto target = GetMousePosition();

    DrawTexture(crosshair, target.x, target.y, WHITE);

    auto v2 = (Vector2){target.x - player->posX, target.y - player->posY};

    player->direction = v2;

    //
    // end player logic
    // -----------------------------------
    // baddie logic
    //

    // std::cerr << "DEBUG: start baddie move loop \n";
    for (auto en = enemies->begin(); en != enemies->end(); en++) {
        // std::cerr << "DEBUG: direction :" << en->direction.x<< "\n";
        if (en->hp > 0) {
            if (en->posX >= SCREENWIDTH || en->posX <= 0) {
                en->direction.x = -en->direction.x;
            }
            if (en->posY >= SCREENHEIGHT || en->posY <= 0) {
                en->direction.y = -en->direction.y;
            }
            if (en->posX >= player->posX) {
                en->posX -= MINION_SPEED;
                en->direction.x -= 0.1f;
            }
            if (en->posY >= player->posY) {
                en->posY -= MINION_SPEED;
                en->direction.y -= 0.1f;
            }
            if (en->posX <= player->posX) {
                en->posX += MINION_SPEED;
                en->direction.x += 0.1f;
            }
            if (en->posY <= player->posY) {
                en->posY += MINION_SPEED;
                en->direction.y += 0.1f;
            }
            if ((en->currentWeapon != nullptr) &&
                (GetRandomValue(0, 100) ==
                 50)  // make enemy fire at random intervals
            ) {
                en->currentWeapon->bang(enemies, &(*en));
                nEnemies++;
                return (
                    0);  // NOTE: this return is here to make sure that we don't
                         // run into a segfault if adding an enemy to the vector
                         // in case it reallocs and invalidates the iterator.
            }
        } else {
            if (en->posX >= SCREENWIDTH || en->posX <= 0 ||
                en->posY >= SCREENHEIGHT) {
                enemies->erase(en);
                std::cerr << "DEBUG: delete baddie" << std::endl;
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
    if (player->currentWeapon->hasProjectiles) {
        projectiles->push_back(player->currentWeapon->getProjectile());
    }
    if (player->currentWeapon->empty == true) {
        player->reloadTime = GetTime();
    }
    return (0);
}

std::string const& Game::getNext() const {
    return level->next;
}

std::string const& Game::getCurrent() const {
    return level->current;
}

std::string const& Game::getBackground() const {
    return level->background;
}

int const& Game::getKills() const {
    return player->victims;
}
