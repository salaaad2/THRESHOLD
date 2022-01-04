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

class Game {
    int nEnemies;

    std::vector<Entity> * enemies;

    Entity * player;

    std::string next;

    public:
        Game(std::string const & path);
        ~Game();

        void start() const ;
        void draw() const ;
        int tick() const ;
        int getKeys() const ;
        int shoot() const ;

        std::string const & getNext() const ;
};

#endif // GAMEPLAY_H_
