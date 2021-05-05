#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#include "Obstacle.h"
class Tile;
class Box : public Obstacle {
public:
    void init(int i, int j);
};

#endif // BOX_H_INCLUDED
