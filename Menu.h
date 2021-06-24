#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "TextManager.h"
#include <iostream>
#include "SDL2/SDL_image.h"
using namespace std;

const int CHANGE_XY_POSITION = 0;
const int CHANGE_WIDTH_HEIGHT = 1;
const SDL_Color WHITE = {255, 255, 255, 255};
class MenuItem {
public:
    int width = 768;
    int height = 832;
    TextInfo textInfo;
    SDL_Texture *placeholder, *text;
    SDL_Surface *tmpSurf;
    SDL_Color color;
    SDL_Rect srcTextRect, dstTextRect, srcPlaceholderRect, dstPlaceholderRect;
    void init(string title, string fontPath, SDL_Color color, int fontSize, const char* texturePath, SDL_Renderer *renderer);
    void setTextRect(TextInfo info);
    void setTextRect(TextInfo info, int value1, int value2, const int xRw);
    void setTextRect(int width, int height, int x, int y);
    void setPlaceholderRect(int width, int height, int x, int y, int srcW, int srcH, int srcX, int srcY);
};
class Menu {
private:
    const int WALKING_ANIMATION_FRAMES = 6;
    int lastPassedLevel;
    int time = 0;
    int sum = 0;
    int chapterSpeed = 8;
    int chapterStep = 0;
    int frame_last_changed = 300;
    int speed = 3;
    int width = 768;
    int height = 836;
    bool isChapterSelectDone = false;
    bool isChainDone = false;
    bool isIntroFaded = false;
    bool isIntroActive = false;
    bool isTitleDone = false;
    bool isBtnChosen = false;
    bool isChapterSelectActive = false;
    int menuActiveBtn = 0;
    int chapterActiveBtn = 0;
    SDL_Surface *temp_surf;
    SDL_Texture *chain[5], *background, *chapterChain[5];
    SDL_Rect introRect, titleRect, chainRect[5], backgroundRect, chapterChainRect[5], introFooterR[2], nameR;
    SDL_Color color;
    MenuItem *title = NULL, *item[4], *chapter[5];
    SDL_Renderer *renderer = NULL;
    TextManager *textManager = NULL;
    TextInfo intro, introFooter[2], nameT;
    void rectSet(TextInfo info, SDL_Rect &rect);
    void rectSet(TextInfo info, SDL_Rect &rect, int x, int y);
    void rectSet(SDL_Rect &rect, int x, int y, int w, int h);
    int position = 1;
public:
    bool isMenuDone = false;
    string name;
    bool isMainMenuActive = false;
    bool isProfileActive = false;
    void init(SDL_Renderer *renderer_, bool status);
    void update();
    void render();
    void setChapterSelectActive(int active);
    void setMenuActiveBtn(int direction);
    void setChapterActiveBtn(int direction);
    int getMenuActiveBtn();
    int getChapterActiveBtn();
    void setMenuActive(bool status);
    bool getMenuActive();
    bool getChapterSelectActive();
    bool getChapterSelectDone();
    int getLastPassedLevel();
    void createHello(string name);
    void setLastPassedLevel(int level);
    void setZero();
    void destroy();
};

#endif // MENU_H_INCLUDED
