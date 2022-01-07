/*********************************/
/*   THRESHOLD        (  //      */
/*   gameplayh         ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "terrain.hpp"
#include "window.hpp"
#include "entity.hpp"

#include <vector>
#include <iostream>

// sound defines
#define SHOTTY_BANG    "../meta/media/mp3/shotty_shoot.mp3"
#define SHOTTY_RELOAD  "../meta/media/mp3/shotty_reload.mp3"

#define AR_BANG    "../meta/media/mp3/ar_shoot.mp3"
#define AR_RELOAD  "../meta/media/mp3/shotty_reload.mp3"


// player textures
#define MUCHACHO_TEX "../meta/media/sprites/cowboy_idle.png"

// bad boy textures
#define SBIRE_TEX_IDLE "../meta/media/sprites/sbire_idle.png"
#define SBIRE_TEX_HURT "../meta/media/sprites/sbire_hurt.png"

// TODO: boss textures

#define COOLPURPLE CLITERAL(Color){ 170, 153, 255, 255 }    // cool Purple
//rgb(170,153,255)
class Game {
    int nEnemies; // number of enemies on given level

    std::vector<Entity> * enemies;

    std::vector<Terrain*> * terrain;

    Entity * player;

    std::string next; // next level
    std::string current; // next level

    Camera2D * camera;

    int frameWidth;
    int frameHeight;

    Rectangle sourceRec;

    Vector2 origin;

  public:
    Game(std::string const &path);
    ~Game();

    void start() ;
    void draw() const;
    int tick() const;
    int getKeys() const;
    int shoot() const;
    int hit(Entity en, Vector2 add1, Vector2 add2) const ;

    std::string const &getNext() const; // returns next level's string
    std::string const &getCurrent() const; // returns next level's string
};

#endif // GAMEPLAY_H_
