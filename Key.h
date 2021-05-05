#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#include "GameObject.h"

class Key : public GameObject {
protected:
    bool destroyFlag = false;
    int keyId;
public:
    TilePosition *tilePosition;
    void init(int i, int j, int id);
    void render();
    void setDestroyFlag();
    bool getDestroyFlag();
    int getKeyId();
};

#endif // KEY_H_INCLUDED
