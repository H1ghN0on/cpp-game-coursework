#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "Box.h"
#include "Monster.h"
#include "Key.h"
#include "Lock.h"

class Tile : public GameObjectPosition {
protected:
    int type;
public:
    Key *key = NULL;
    Box *obstacle = NULL;
    Monster *monster = NULL;
    Lock *lock = NULL;
    int getType();
    void setType(const int &u_type);
};

#endif // TILE_H_INCLUDED
