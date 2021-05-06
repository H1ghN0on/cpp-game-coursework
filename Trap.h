#ifndef TRAP_H_INCLUDED
#define TRAP_H_INCLUDED

#include "GameObject.h"

class Trap : public GameObject {
protected:
    bool isActive;
public:
    void init(int i, int j, int active);
    bool getActive();
    void setActive(bool active);
};

#endif // TRAP_H_INCLUDED
