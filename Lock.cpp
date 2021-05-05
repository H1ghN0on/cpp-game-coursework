#include "Lock.h"
#include "Tile.h"
void Lock :: init(int i, int j, int id) {
    lockId = id;
    tilePosition = new TilePosition;
    destObjectR.w = srcObjectR.w = 64;
    destObjectR.h = srcObjectR.h = 64;
    srcObjectR.x = 0;
    srcObjectR.y = 0;
    tile[i][j].lock -> setX(tile[i][j].getX());
    tile[i][j].lock -> setY(tile[i][j].getY());
    tilePosition -> str = i;
    tilePosition -> col = j;
    objectTexture = IMG_LoadTexture(renderer, "assets/lock.png");
}

void Lock :: render() {
    destObjectR.x = getX();
    destObjectR.y = getY();
    SDL_RenderCopy(renderer, objectTexture, &srcObjectR, &destObjectR);
}

int Lock :: getLockId() {
    return lockId;
}

void Lock :: setDestroyFlag() {
    destroyFlag = true;
}

bool Lock :: getDestroyFlag() {
    return destroyFlag;
}