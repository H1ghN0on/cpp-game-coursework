#ifndef LOCK_H_INCLUDED
#define LOCK_H_INCLUDED

#include "KeyLockSystem.h"

class Lock : public KeyLockSystem {
protected:
    int lockId;
public:
    void init(int i, int j, int id);
    int getLockId();
};

#endif // LOCK_H_INCLUDED
