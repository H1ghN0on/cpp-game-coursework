#ifndef KEYLOCKSYSTEM_H_INCLUDED
#define KEYLOCKSYSTEM_H_INCLUDED

#include "GameObject.h"

class KeyLockSystem : public GameObject {
protected:
    bool destroyFlag = false;
public:
    void setDestroyFlag();
    bool getDestroyFlag();
};


#endif // KEYLOCKSYSTEM_H_INCLUDED
