#include "Trap.h"
#include "Tile.h"
void Trap :: init(int i, int j, int active) {
    isActive = active;
    destObjectR.w = srcObjectR.w = textureSize;
    destObjectR.h = srcObjectR.h = textureSize;
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
        SDL_DestroyTexture(objectTexture);
        objectTexture = IMG_LoadTexture(renderer, "assets/trap-active.png");

    } else {
        SDL_DestroyTexture(objectTexture);
        objectTexture = IMG_LoadTexture(renderer, "assets/trap.png");
    }
}
