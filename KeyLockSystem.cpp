#include "KeyLockSystem.h"

void KeyLockSystem :: setDestroyFlag() {
    destroyFlag = true;
}

bool KeyLockSystem :: getDestroyFlag() {
    return destroyFlag;
}
