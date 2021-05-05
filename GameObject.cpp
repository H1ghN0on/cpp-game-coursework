#include "GameObject.h"
#include "Tile.h"
#include <iostream>
using namespace std;
SDL_Renderer* GameObject :: renderer;
Tile** GameObject :: tile;
GameObject :: GameObject() {

}

GameObject :: GameObject(SDL_Renderer* u_renderer) {
    renderer = u_renderer;
}

void GameObject :: setMap(Tile **u_tile) {
    tile = u_tile;
}
