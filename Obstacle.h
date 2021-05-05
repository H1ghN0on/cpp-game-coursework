#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED
#include "DynamicGameObject.h"
class Tile;
class Obstacle : public DynamicGameObject {
public:
    TilePosition *tilePosition;
    MoveInfo *move;
    void update();
    void moveTo(int direction);
    ~Obstacle();
};

#endif // OBSTACLE_H_INCLUDED
