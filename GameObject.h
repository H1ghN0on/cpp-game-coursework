#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GameObjectPosition.h"
class Tile;
class GameObject : public GameObjectPosition {
protected:
    GameObject();
    class TilePosition {
    public:
        int str;
        int col;
    };
    static SDL_Renderer *renderer;
    static Tile **tile;
    SDL_Texture *objectTexture = NULL;
    SDL_Rect destObjectR, srcObjectR;

public:
    GameObject(SDL_Renderer *u_renderer);
    void setMap(Tile **u_tile);
    virtual void render();
};

#endif // GAMEOBJECT_H_INCLUDED
