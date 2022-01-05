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


#define COOLPURPLE CLITERAL(Color){ 170, 153, 255, 255 }    // cool Purple
//rgb(170,153,255)
class Game {
    int nEnemies; // number of enemies on given level

    std::vector<Entity> * enemies;

    std::vector<Terrain*> * terrain;

    Entity * player;

    std::string next; // next level

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
};

#endif // GAMEPLAY_H_
