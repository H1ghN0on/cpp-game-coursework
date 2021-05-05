#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <vector>
#include "Box.h"
#include "Monster.h"
#include "Key.h"
#include "Lock.h"
#include "Trap.h"
class Tile : public GameObjectPosition {
protected:

public:
    std :: vector <int> type;
    Key *key = NULL;
    Box *obstacle = NULL;
    Monster *monster = NULL;
    Lock *lock = NULL;
    Trap *trap = NULL;
    std :: vector<int> getType();
    void setType(const int &u_type);
    void delType(const int &u_type);
    bool findType(const int &u_type);
};

#endif // TILE_H_INCLUDED
