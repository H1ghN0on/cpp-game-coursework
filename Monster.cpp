#include "Monster.h"
#include "Tile.h"
#include <iostream>
using namespace std;
void Monster :: init(int i, int j) {
    moveInfo = new MoveInfo;
    tilePosition = new TilePosition;
    destObjectR.w = srcObjectR.w = textureSize;
    destObjectR.h = srcObjectR.h = textureSize;
    srcObjectR.x = 0;
    srcObjectR.y = 0;
    tile[i][j].monster -> setX(tile[i][j].getX());
    tile[i][j].monster -> setY(tile[i][j].getY());
    tilePosition -> str = i;
    tilePosition -> col = j;
    moveInfo -> step = 2;
    moveInfo -> remain = 0;
    moveInfo -> direction = 0;
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
