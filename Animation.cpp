#include "Animation.h"

bool Animation :: checkFrame(int counter) {
    if (counter == frame) {
        return true;
    } else {
        return false;
    }
}
