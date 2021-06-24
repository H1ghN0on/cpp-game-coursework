#include "Star.h"
#include "Tile.h"
void Star :: init(int i, int j) {
    destObjectR.w = srcObjectR.w = textureSize;
    destObjectR.h = srcObjectR.h = textureSize;
    srcObjectR.x = 0;
    srcObjectR.y = 0;
    tile[i][j].star -> setX(tile[i][j].getX());
    tile[i][j].star -> setY(tile[i][j].getY());
    tilePosition -> str = i;
    tilePosition -> col = j;
    objectTexture = IMG_LoadTexture(renderer, "assets/nezuko.png");
}
