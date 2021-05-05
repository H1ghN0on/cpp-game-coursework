#include "Box.h"
#include "Tile.h"
#include <iostream>
using namespace std;

void Box :: init(int i, int j) {
    move = new MoveInfo;
    tilePosition = new TilePosition;
    destObjectR.w = srcObjectR.w = 64;
    destObjectR.h = srcObjectR.h = 64;
    srcObjectR.x = 0;
    srcObjectR.y = 0;
    tile[i][j].obstacle -> setX(tile[i][j].getX());
    tile[i][j].obstacle -> setY(tile[i][j].getY());
    tilePosition -> str = i;
    tilePosition -> col = j;
    move -> step = 2;
    move -> remain = 0;
    move -> direction = 0;
    objectTexture = IMG_LoadTexture(renderer, "assets/box.png");
}
