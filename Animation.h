#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
class Animation {
protected:
    const int FPS = 20;
    const int frame = 1000 / FPS;
    int counter = 0;
    SDL_Renderer *rendererAnim;
    SDL_Texture *staying;
    SDL_Texture *moving;
    SDL_Texture *activeTexture;
    SDL_Rect destObject, srcObject;
public:
    virtual void stay() = 0;
    bool checkFrame(int counter);
};

#endif // ANIMATION_H_INCLUDED
