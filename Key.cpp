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

int Key :: getKeyId() {
    return keyId;
}
