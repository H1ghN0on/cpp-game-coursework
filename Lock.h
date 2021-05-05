#ifndef LOCK_H_INCLUDED
#define LOCK_H_INCLUDED

#include "GameObject.h"

class Lock : public GameObject {
protected:
    bool destroyFlag = false;
    int lockId;
public:
    TilePosition *tilePosition;
    void init(int i, int j, int id);
    void render();
    void setDestroyFlag();
    int getLockId();
    bool getDestroyFlag();
};

#endif // LOCK_H_INCLUDED
