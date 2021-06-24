#ifndef ACHIEVEMENTS_H_INCLUDED
#define ACHIEVEMENTS_H_INCLUDED

#include <iostream>
#include "TextManager.h"
#include "SDL2/SDL_image.h"

class AchievementBox {
public:
    TextInfo info;
    SDL_Rect achievementR, statusR;
    bool status;
};
class Achievements {
private:
    TextManager textManager;
    SDL_Renderer *renderer;
    SDL_Texture *wing, *cross;
    AchievementBox achievements[5];
    void setRect(SDL_Rect &rect, int width, int height, int x, int y);
public:
    void init(SDL_Renderer *renderer, int lastPassedLevel);
    void render();
    void update(int lastPassedLevel);
};

#endif // ACHIEVEMENTS_H_INCLUDED
