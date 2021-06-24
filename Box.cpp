#include "Box.h"
#include "Tile.h"
#include <iostream>
using namespace std;

void Box :: init(int i, int j) {
    destObjectR.w = srcObjectR.w = textureSize;
    destObjectR.h = srcObjectR.h = textureSize;
    srcObjectR.x = 0;
    srcObjectR.y = 0;
    tile[i][j].obstacle -> setX(tile[i][j].getX());
    tile[i][j].obstacle -> setY(tile[i][j].getY());
    tilePosition -> str = i;
    tilePosition -> col = j;
    moveInfo -> step = 2;
    moveInfo -> remain = 0;
    moveInfo -> direction = 0;
    objectTexture = IMG_LoadTexture(renderer, "assets/box.png");
}
