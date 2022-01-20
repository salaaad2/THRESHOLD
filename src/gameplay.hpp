/*********************************/
/*   THRESHOLD        (  //      */
/*   gameplayh         ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "entity.hpp"
#include "map.hpp"
#include "terrain.hpp"
#include "window.hpp"

#include <raylib.h>
#include <iostream>
#include <vector>

// sound defines
#define SHOTTY_BANG "../meta/media/mp3/shotty_shoot.mp3"
#define SHOTTY_RELOAD "../meta/media/mp3/shotty_reload.mp3"

#define AR_BANG "../meta/media/mp3/ar_shoot.mp3"
#define AR_RELOAD "../meta/media/mp3/shotty_reload.mp3"

// player textures
#define MUCHACHO_TEX "../meta/media/sprites/cowboy_idle.png"

// crosshair
#define CROSSHAIR_TEX "../meta/media/sprites/crosshair.png"

// bad boy textures
#define SBIRE_TEX_IDLE "../meta/media/sprites/sbire_idle.png"
#define SBIRE_TEX_HURT "../meta/media/sprites/sbire_hurt.png"

// boss textures
#define BOSS_TEX_IDLE "../meta/media/sprites/boss_idle.png"
#define BOSS_TEX_HURT "../meta/media/sprites/boss_hurt.png"
#define BOSS_TEX_DEAD "../meta/media/sprites/boss_hurt.png"

// #define COOLPURPLE \
//     CLITERAL(Color) { 170, 153, 255, 255 }  // cool Purple
#define COOLPURPLE \
    CLITERAL(Color) { 153, 0, 0, 255 }  // cool Purple

class Game {
    int nEnemies;  // number of enemies on given level
    int nWaves;    // number of waves in level
    int nPerWave;  // number of enemies per wave.

    // NOTE : maps are assumed to be correct. therefore, no
    // checks are made to verify their integrity.
    // having wrong maps can (and probably will) result in a crash

    std::vector<Entity>* enemies;

    Entity* player;

    std::string next;        // next level
    std::string current;     // next level
    std::string background;  // next level
    Level* level;

    int frameWidth;
    int frameHeight;

    Rectangle sourceRec;

    Vector2 origin;

    Texture2D crosshair;

   public:
    Game(std::string const& path);
    ~Game();

    Level* parse(std::string const& path);
    void draw();
    int tick();
    int getKeys();
    int shoot() const;
    int hit(Entity en, Vector2 add1, Vector2 add2) const;

    std::string const& getNext() const;        // returns next level's string
    std::string const& getCurrent() const;     // returns next level's string
    std::string const& getBackground() const;  // returns next level's string
    int const& getKills() const;               // returns next level's string
};

#endif  // GAMEPLAY_H_
