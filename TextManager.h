#ifndef TEXTMANAGER_H_INCLUDED
#define TEXTMANAGER_H_INCLUDED
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

using namespace std;
class TextInfo {
public:
    SDL_Texture *texture = NULL;
    int xPosition, yPosition, width, height;
    SDL_Color color;
    std :: string text;
};

class TextManager {
private:
    SDL_Texture *image;
public:
    int width = 768;
    int height = 832;
    void init();
    int x, y, iW, iH;
    TextInfo renderText(const std::string &message, const std::string &fontFile,SDL_Color color, int fontSize, SDL_Renderer *renderer, int, int);
    TextInfo renderText(const std::string &message, const std::string &fontFile,SDL_Color color, int fontSize, SDL_Renderer *renderer);
};

#endif // TEXTMANAGER_H_INCLUDED
