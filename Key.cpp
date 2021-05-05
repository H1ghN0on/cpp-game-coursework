#include "Key.h"
#include "Tile.h"
void Key :: init(int i, int j, int id) {
    keyId = id;
    tilePosition = new TilePosition;
    destObjectR.w = srcObjectR.w = 64;
    destObjectR.h = srcObjectR.h = 64;
    srcObjectR.x = 0;
    srcObjectR.y = 0;
    tile[i][j].key -> setX(tile[i][j].getX());
    tile[i][j].key -> setY(tile[i][j].getY());
    tilePosition -> str = i;
    tilePosition -> col = j;
    objectTexture = IMG_LoadTexture(renderer, "assets/key.png");
}

void Key :: render() {
    destObjectR.x = getX();
    destObjectR.y = getY();
    SDL_RenderCopy(renderer, objectTexture, &srcObjectR, &destObjectR);
}

void Key :: setDestroyFlag() {
    destroyFlag = true;
}

bool Key :: getDestroyFlag() {
    return destroyFlag;
}

int Key :: getKeyId() {
    return keyId;
}
