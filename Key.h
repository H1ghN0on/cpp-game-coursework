#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#include "KeyLockSystem.h"

class Key : public KeyLockSystem {
protected:
    int keyId;
public:
    void init(int i, int j, int id);
    int getKeyId();
};

#endif // KEY_H_INCLUDED
