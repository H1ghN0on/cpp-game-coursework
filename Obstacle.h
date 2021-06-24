#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED
#include "DynamicGameObject.h"
class Tile;
class Obstacle : public DynamicGameObject {
private:
    bool flag = false;
public:
    void update();
    void moveTo(int direction);
};

#endif // OBSTACLE_H_INCLUDED
