#ifndef MAP_H
#define MAP_H

#include <iostream>

typedef struct Level {
    int nPerWave;
    int nWaves;
    int nTotal;

    int nGrunts;
    int gRadius;
    int gHp;

    int nBoss;
    int bRadius;
    int bHp;

    int nMinion;
    int mRadius;
    int mHp;

    std::string next;        // next level
    std::string current;     // next level
    std::string background;  // next level
} Level;

#endif /* MAP_H */
