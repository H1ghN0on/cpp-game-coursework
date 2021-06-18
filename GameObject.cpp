#include "GameObject.h"
#include "Tile.h"
#include <iostream>
using namespace std;
SDL_Renderer* GameObject :: renderer;
Tile** GameObject :: tile;
int GameObject :: textureSize;
GameObject :: GameObject() {

}

GameObject :: GameObject(SDL_Renderer* u_renderer, int textureSize_) {
    renderer = u_renderer;
    textureSize = textureSize_;
    destObjectR.w = srcObjectR.w = textureSize;
    destObjectR.h = srcObjectR.h = textureSize;
}

void GameObject :: setMap(Tile **u_tile) {
    tile = u_tile;
}

void GameObject :: render() {
    destObjectR.x = getX();
    destObjectR.y = getY();
    SDL_RenderCopy(renderer, objectTexture, &srcObjectR, &destObjectR);
}

GameObject :: ~GameObject() {
    SDL_DestroyTexture(objectTexture);
}
