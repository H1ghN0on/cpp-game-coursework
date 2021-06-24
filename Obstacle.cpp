#include "Obstacle.h"
#include <iostream>
#include "Tile.h"
using namespace std;
void Obstacle :: update() {
    switch (moveInfo -> direction) {
        case 0: {
            break;
        }
        case 1: {
//            if (moveInfo -> remain) {
//                this -> setY(y - moveInfo -> step);
//                destObjectR.y = this -> getY();
//                moveInfo -> remain--;
//                return;
//            }
            this -> setY(y - 64);
            destObjectR.y = this -> getY();
            moveInfo -> remain = 1;
            if (!flag) {
                flag = true;
            } else {
                flag = false;
                moveInfo -> direction = 0;
            }
            break;
        }
        case 2: {
//            if (moveInfo -> remain) {
//                this -> setX(x + moveInfo -> step);
//                destObjectR.x = this -> getX();
//                moveInfo -> remain--;
//                return;
//            }
            this -> setX(x + 64);
            destObjectR.x = this -> getX();
            moveInfo -> remain = 1;
            if (!flag) {
                flag = true;
            } else {
                flag = false;
                moveInfo -> direction = 0;
            }
            break;
        }
        case 3: {
//            if (moveInfo -> remain) {
//                this -> setY(y + moveInfo -> step);
//                destObjectR.y = this -> getY();
//                moveInfo -> remain--;
//                return;
//            }
            this -> setY(y + 64);
            destObjectR.y = this -> getY();
            moveInfo -> remain = 1;
            if (!flag) {
                flag = true;
            } else {
                flag = false;
                moveInfo -> direction = 0;
            }
            break;
        }
        case 4: {
//            if (moveInfo -> remain) {
//                this -> setX(x - moveInfo -> step);
//                destObjectR.x = this -> getX();
//                moveInfo -> remain--;
//                return;
//            }
            this -> setX(x - 64);
            destObjectR.x = this -> getX();
            moveInfo -> remain = 1;
            if (!flag) {
                flag = true;
            } else {
                flag = false;
                moveInfo -> direction = 0;
            }
            break;
        }
    }
}
void Obstacle :: moveTo(int direction) {
    moveInfo -> remain = textureSize / moveInfo -> step;
    switch (direction) {
        //top
        case 1: {
            moveInfo -> direction = 1;
            break;
        }
        // right
        case 2: {
            moveInfo -> direction = 2;
            break;
        }
        //down
        case 3: {
            moveInfo -> direction = 3;
            break;
        }
        //left
        case 4: {
            moveInfo -> direction = 4;
            break;
        }
    }
}
