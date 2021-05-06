#ifndef DYNAMICGAMEOBJECT_H_INCLUDED
#define DYNAMICGAMEOBJECT_H_INCLUDED

#include "GameObject.h"

class DynamicGameObject : public GameObject {
protected:
    class MoveInfo {
    public:
        int direction;
        int step;
        int remain;
    };
public:
    MoveInfo *move = NULL;
};

#endif // DYNAMICGAMEOBJECT_H_INCLUDED
