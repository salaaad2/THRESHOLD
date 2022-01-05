#include "terrain.hpp"

#include <iostream>

#include "raylib.h"

Terrain::Terrain(int const & x, int const & y, int const & thick)
    : x(x), y(y), thick(thick)
{
    std::cout << "\ncreate new terrain with parameters :\n" << this->x << " " << this->y << " " << this->thick << std::endl;
}

Terrain::~Terrain(void) {
    std::cout << "destroy terrain\n";
}
