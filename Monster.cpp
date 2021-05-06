#include "Monster.h"
#include "Tile.h"
#include <iostream>
using namespace std;
void Monster :: init(int i, int j) {
    move = new MoveInfo;
    tilePosition = new TilePosition;
    destObjectR.w = srcObjectR.w = 64;
    destObjectR.h = srcObjectR.h = 64;
    srcObjectR.x = 0;
    srcObjectR.y = 0;
    tile[i][j].monster -> setX(tile[i][j].getX());
    tile[i][j].monster -> setY(tile[i][j].getY());
    tilePosition -> str = i;
    tilePosition -> col = j;
    move -> step = 2;
    move -> remain = 0;
    move -> direction = 0;
    objectTexture = IMG_LoadTexture(renderer, "assets/monster.png");
}

void Monster :: setDestroyFlag() {
    destroyFlag = true;
}

bool Monster :: getDestroyFlag() {
    return destroyFlag;
}

Monster :: ~Monster() {
//    delete tilePosition;
}
