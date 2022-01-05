/*********************************/
/*   THRESHOLD        (  //      */
/*   gameplayh         ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "window.hpp"
#include "entity.hpp"

#include <vector>
#include <iostream>


#define COOLPURPLE CLITERAL(Color){ 170, 153, 255, 255 }    // cool Purple
//rgb(170,153,255)
class Game {
    int nEnemies; // number of enemies on given level

    std::vector<Entity> * enemies;

    Entity * player;

    std::string next; // next level

    Camera2D * camera;

    public:
        Game(std::string const & path);
        ~Game();

        void start() const ;
        void draw() const ;
        int tick() const ;
        int getKeys() const ;
        int shoot() const ;

        std::string const & getNext() const ; // returns next level's string
};

#endif // GAMEPLAY_H_
