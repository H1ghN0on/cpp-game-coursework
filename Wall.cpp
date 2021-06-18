#include "Wall.h"
#include "Tile.h"

void Wall :: init(int i, int j) {
    tilePosition = new TilePosition;
    destObjectR.w = srcObjectR.w = textureSize;
    destObjectR.h = srcObjectR.h = textureSize;
    srcObjectR.x = 0;
    srcObjectR.y = 0;
    tile[i][j].wall -> setX(tile[i][j].getX());
    tile[i][j].wall -> setY(tile[i][j].getY());
    tilePosition -> str = i;
    tilePosition -> col = j;
    objectTexture = IMG_LoadTexture(renderer, "assets/wall.png");
}
