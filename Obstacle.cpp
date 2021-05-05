#include "Obstacle.h"
#include <iostream>
#include "Tile.h"
using namespace std;
void Obstacle :: update() {
    switch (move -> direction) {
        case 0: {
            break;
        }
        case 1: {
            if (move -> remain) {
                this -> setY(y - move -> step);
                destObjectR.y = this -> getY();
                move -> remain--;
                return;
            }
            move -> direction = 0;
            break;
        }
        case 2: {
            if (move -> remain) {
                this -> setX(x + move -> step);
                destObjectR.x = this -> getX();
                move -> remain--;
                return;
            }
            move -> direction = 0;
            break;
        }
        case 3: {
            if (move -> remain) {
                this -> setY(y + move -> step);
                destObjectR.y = this -> getY();
                move -> remain--;
                return;
            }
            move -> direction = 0;
            break;
        }
        case 4: {
            if (move -> remain) {
                this -> setX(x - move -> step);
                destObjectR.x = this -> getX();
                move -> remain--;
                return;
            }
            move -> direction = 0;
            break;
        }
    }
}
void Obstacle :: moveTo(int direction) {
    move -> remain = 64 / move -> step;
    switch (direction) {
        //top
        case 1: {
            move -> direction = 1;
            break;
        }
        // right
        case 2: {
            move -> direction = 2;
            break;
        }
        //down
        case 3: {
            move -> direction = 3;
            break;
        }
        //left
        case 4: {
            move -> direction = 4;
            break;
        }
    }
}

void Obstacle :: render() {
    destObjectR.x = getX();
    destObjectR.y = getY();
    SDL_RenderCopy(renderer, objectTexture, &srcObjectR, &destObjectR);
}

Obstacle :: ~Obstacle() {
    delete move;
    delete tilePosition;
}
