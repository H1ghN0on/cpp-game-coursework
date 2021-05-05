#include "Trap.h"
#include "Tile.h"
void Trap :: init(int i, int j, int active) {
    isActive = active;
    tilePosition = new TilePosition;
    destObjectR.w = srcObjectR.w = 64;
    destObjectR.h = srcObjectR.h = 64;
    srcObjectR.x = 0;
    srcObjectR.y = 0;
    tile[i][j].trap -> setX(tile[i][j].getX());
    tile[i][j].trap -> setY(tile[i][j].getY());
    tilePosition -> str = i;
    tilePosition -> col = j;
    if (isActive) {
        objectTexture = IMG_LoadTexture(renderer, "assets/trap-active.png");
    } else {
        objectTexture = IMG_LoadTexture(renderer, "assets/trap.png");
    }

}

bool Trap :: getActive() {
    return isActive;
}

void Trap :: setActive(bool active) {
    isActive = active;
    if (isActive) {
        objectTexture = IMG_LoadTexture(renderer, "assets/trap-active.png");
    } else {
        objectTexture = IMG_LoadTexture(renderer, "assets/trap.png");
    }
}
