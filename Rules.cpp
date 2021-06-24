#include "Rules.h"

void Rules :: init(SDL_Renderer *renderer_) {
    renderer = renderer_;
    box = createTexture("assets/box.png");
    monster = createTexture("assets/monster.png");
    key = createTexture("assets/key.png");
    lock = createTexture("assets/lock.png");
    trap = createTexture("assets/trap-active.png");
    star = createTexture("assets/nezuko.png");
    title = textManager.renderText("RULES" ,"fonts/CaligulaDodgy.ttf", {255, 255, 255, 255}, 80, renderer);
    setRect(titleR, title.width, title.height, title.xPosition, 25);
    int counter = 150;
    for (int i = 0; i < 7; i++) {
        string name;
        switch (i) {
            case 0: {
                name = "Each action costs 1 step";
                break;
            }
            case 1: {
                name = "Push           to clear the way out";
                break;
            }
            case 2: {
                name = "Push           to the obstacles to destroy them";
                break;
            }
            case 3: {
                name = "Find the           to unlock the           ";
                break;
            }
            case 4: {
                name = "Beware the           to avoid the fine";
                break;
            }
            case 5: {
                name = "Reach the           to pass the level";
                break;
            }
            case 6: {
                name = "The number of steps is limited";
                break;
            }
        }
        rule[i] = textManager.renderText(name ,"fonts/Leo Normal.ttf", {126, 155, 125, 255}, 35, renderer);
        setRect(ruleR[i], rule[i].width, rule[i].height, 15, counter);
        counter += rule[i].height + 30;
    }
    setRect(boxR, 64, 64, ruleR[1].x + 95, ruleR[1].y - 13);
    setRect(monsterR, 64, 64, ruleR[2].x + 95, ruleR[2].y - 13);
    setRect(keyR, 64, 64, ruleR[3].x + 140, ruleR[3].y - 13);
    setRect(lockR, 64, 64, ruleR[3].x + 445, ruleR[3].y - 13);
    setRect(trapR, 64, 64, ruleR[4].x + 195, ruleR[4].y - 13);
    setRect(starR, 64, 64, ruleR[5].x + 170, ruleR[5].y - 13);
    continueAccept = textManager.renderText("Press Enter to conitnue...", "fonts/Leo Normal.ttf", color, 32, renderer);
    setRect(continueAcceptR, continueAccept.width, continueAccept.height, 400, 700);
}

void Rules :: setRect(SDL_Rect &rect, int width, int height, int x, int y) {
    rect.w = width;
    rect.h = height;
    rect.x = x;
    rect.y = y;
}

SDL_Texture* Rules :: createTexture(const char* path) {
    SDL_Surface *temp_surf = NULL;
    SDL_Texture *texture = NULL;
    temp_surf = IMG_Load(path);
    texture = SDL_CreateTextureFromSurface(renderer, temp_surf);
    SDL_FreeSurface(temp_surf);
    return texture;
}

void Rules :: update() {
    int opacity = static_cast<int>(color.a);
    isFaded ? opacity++ : opacity--;
    if (opacity != 255 && opacity != 0) {
        color.a = opacity;
        SDL_DestroyTexture(continueAccept.texture);
        continueAccept = textManager.renderText("Press Enter to conitnue...", "fonts/Leo Normal.ttf", color, 32, renderer);
        SDL_Delay(3);
    } else if (opacity == 255) {
        isFaded = false;
    } else if (opacity == 0) {
        isFaded = true;
    }
}

void Rules :: render() {
    SDL_RenderCopy(renderer, box, NULL, &boxR);
    SDL_RenderCopy(renderer, monster, NULL, &monsterR);
    SDL_RenderCopy(renderer, key, NULL, &keyR);
    SDL_RenderCopy(renderer, lock, NULL, &lockR);
    SDL_RenderCopy(renderer, trap, NULL, &trapR);
    SDL_RenderCopy(renderer, star, NULL, &starR);
    SDL_RenderCopy(renderer, title.texture, NULL, &titleR);
    for (int i = 0; i < 7; i++) {
        SDL_RenderCopy(renderer, rule[i].texture, NULL, &ruleR[i]);
    }
        SDL_RenderCopy(renderer, continueAccept.texture, NULL, &continueAcceptR);

}
