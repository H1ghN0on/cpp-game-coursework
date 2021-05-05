#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED
#include "GameObject.h"
class Tile;
class Obstacle : public GameObject {
public:
    TilePosition *tilePosition;
    MoveInfo *move;
    void update();
    void moveTo(int direction);
    void render();
    ~Obstacle();
};

#endif // OBSTACLE_H_INCLUDED
