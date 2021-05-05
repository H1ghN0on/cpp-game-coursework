#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "Box.h"
#include "Monster.h"

class Tile : public GameObjectPosition {
protected:
    int type;
public:
    Box *obstacle = NULL;
    Monster *monster = NULL;
    int getType();
    void setType(const int &u_type);
};

#endif // TILE_H_INCLUDED
