#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED

#include <iostream>
#include "TextManager.h"
#include "Profile.h"
#include "SDL2/SDL_image.h"

class Rules : public Profile {
private:
    SDL_Color color = {255, 255, 255, 0};
    bool isFaded = true;
    TextManager textManager;
    TextInfo rule[7], continueAccept, title, nameCorrect;
    SDL_Renderer *renderer;
    SDL_Texture *box = NULL, *monster = NULL, *key = NULL, *lock = NULL, *trap = NULL;
    SDL_Rect boxR, monsterR, keyR, lockR, trapR, ruleR[7], continueAcceptR, titleR, nameCorrectR;
    int opacity;
    void setRect(SDL_Rect &rect, int width, int height, int x, int y);
public:
    void init(SDL_Renderer *renderer_);
    SDL_Texture* createTexture(const char* path);
    void update();
    void render();
};

#endif // RULES_H_INCLUDED
