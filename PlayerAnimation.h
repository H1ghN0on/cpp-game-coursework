#ifndef PLAYERANIMATION_H_INCLUDED
#define PLAYERANIMATION_H_INCLUDED
#include "Animation.h"
class PlayerAnimation : public Animation {
protected:
public:
    void stay();
    void move();
    void changeDirection(int direction);
};

#endif // PLAYERANIMATION_H_INCLUDED
