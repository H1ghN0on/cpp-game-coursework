#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include "Obstacle.h"
class Tile;
class Monster : public Obstacle {
private:
    bool destroyFlag = false;
public:
    void init(int i, int j);
    void setDestroyFlag();
    bool getDestroyFlag();
    TilePosition *tilePosition = NULL;
    ~Monster();
};


#endif // MONSTER_H_INCLUDED
