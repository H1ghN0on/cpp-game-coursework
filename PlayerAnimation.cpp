#include "PlayerAnimation.h"

void PlayerAnimation :: stay() {
    counter++;
    if (checkFrame(counter)) {
        srcObject.x += 64;
        if (srcObject.x == 128) {
            srcObject.x = 0;
        }
        counter = 0;
    }
}

void PlayerAnimation :: move() {
    counter++;
    if (checkFrame(counter)) {
        srcObject.x += 64;
        if (srcObject.x == 256) {
            srcObject.x = 0;
        }
        counter = 0;
    }
}

void PlayerAnimation :: changeDirection(int direction) {
    switch (direction) {
        case 1: {
            srcObject.y = 64;
            srcObject.x = 0;
            break;
        }
        case 2: {
            srcObject.y = 128;
            srcObject.x = 0;
            break;
        }
        case 3: {
            srcObject.y = 0;
            srcObject.x = 0;
            break;
        }
        case 4: {
            srcObject.y = 192;
            srcObject.x = 0;
            break;
        }
    }
}
