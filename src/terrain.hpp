#ifndef TERRAIN_H_
#define TERRAIN_H_

class Terrain {
    public:
        Terrain();
        Terrain(int const & x, int const & y, int const & thick);
        ~Terrain();

        void draw() const ;
        int x;
        int y;
        int thick;
};

#endif // TERRAIN_H_
