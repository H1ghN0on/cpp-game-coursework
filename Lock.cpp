#include "Lock.h"
#include "Tile.h"
void Lock :: init(int i, int j, int id) {
    lockId = id;
    destObjectR.w = srcObjectR.w = textureSize;
    destObjectR.h = srcObjectR.h = textureSize;
    srcObjectR.x = 0;
    srcObjectR.y = 0;
    tile[i][j].lock -> setX(tile[i][j].getX());
    tile[i][j].lock -> setY(tile[i][j].getY());
    tilePosition -> str = i;
    tilePosition -> col = j;
    objectTexture = IMG_LoadTexture(renderer, "assets/lock.png");
}

int Lock :: getLockId() {
    return lockId;
}
