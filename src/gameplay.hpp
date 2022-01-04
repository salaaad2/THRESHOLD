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

    public:
        Game(std::string const & path);
        ~Game();

        void start() const ;
        void draw() const ;
        int tick() const ;
        int getKeys() const ;
};

#endif // GAMEPLAY_H_
