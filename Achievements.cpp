#include "Achievements.h"

void Achievements :: init(SDL_Renderer *renderer_, int lastPassedLevel) {
    SDL_Surface *tmpSurf;
    renderer = renderer_;
    int yCounter = 100;
    for (int i = 0; i < lastPassedLevel; i++) {
        string name = "Level " + to_string(i + 1);
        achievements[i].info = textManager.renderText(name, "fonts/Leo Normal.ttf", {255, 255, 255, 255}, 32, renderer);
        achievements[i].status = true;
        setRect(achievements[i].achievementR, achievements[i].info.width, achievements[i].info.height, 100, yCounter);
        setRect(achievements[i].statusR, 50, 50, 600, yCounter - 15);
        yCounter += 150;
    }
    for (int i = lastPassedLevel; i < 5; i++) {
        string name = "Level " + to_string(i + 1);
        achievements[i].info = textManager.renderText(name, "fonts/Leo Normal.ttf", {255, 255, 255, 255}, 32, renderer);
        achievements[i].status = false;
        setRect(achievements[i].achievementR, achievements[i].info.width, achievements[i].info.height, 100, yCounter - 15);
        setRect(achievements[i].statusR, 50, 50, 600, yCounter);
        yCounter += 150;
    }

    tmpSurf = IMG_Load("assets/wing.png");
    wing = SDL_CreateTextureFromSurface(renderer, tmpSurf);
    SDL_FreeSurface(tmpSurf);
    tmpSurf = IMG_Load("assets/cross.png");
    cross = SDL_CreateTextureFromSurface(renderer, tmpSurf);
    SDL_FreeSurface(tmpSurf);
}

void Achievements :: setRect(SDL_Rect &rect, int width, int height, int x, int y) {
    rect.w = width;
    rect.h = height;
    rect.x = x;
    rect.y = y;
}

void Achievements :: update(int lastPassedLevel) {
    int yCounter = 100;
    for (int i = 0; i < lastPassedLevel; i++) {
        SDL_DestroyTexture(achievements[i].info.texture);
        string name = "Level " + to_string(i + 1);
        achievements[i].info = textManager.renderText(name, "fonts/Leo Normal.ttf", {255, 255, 255, 255}, 32, renderer);
        achievements[i].status = true;
        setRect(achievements[i].achievementR, achievements[i].info.width, achievements[i].info.height, 100, yCounter);
        setRect(achievements[i].statusR, 50, 50, 600, yCounter - 15);
        yCounter += 150;
    }
    for (int i = lastPassedLevel; i < 5; i++) {
        SDL_DestroyTexture(achievements[i].info.texture);
        string name = "Level " + to_string(i + 1);
        achievements[i].info = textManager.renderText(name, "fonts/Leo Normal.ttf", {255, 255, 255, 255}, 32, renderer);
        achievements[i].status = false;
        setRect(achievements[i].achievementR, achievements[i].info.width, achievements[i].info.height, 100, yCounter - 15);
        setRect(achievements[i].statusR, 50, 50, 600, yCounter);
        yCounter += 150;
    }
}

void Achievements :: render() {
    for (int i = 0; i < 5; i++) {
        SDL_RenderCopy(renderer, achievements[i].info.texture, NULL, &achievements[i].achievementR);
        achievements[i].status ?
            SDL_RenderCopy(renderer, wing, NULL, &achievements[i].statusR)
            :
            SDL_RenderCopy(renderer, cross, NULL, &achievements[i].statusR);
    }
}
