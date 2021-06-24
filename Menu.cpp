#include "Menu.h"
void MenuItem :: init(
        string title,
        string fontPath,
        SDL_Color color,
        int fontSize,
        const char*
        texturePath,
        SDL_Renderer *renderer
    )
{
    TextManager textManager;
    textInfo = textManager.renderText(title,fontPath, color, fontSize, renderer);
    text = textInfo.texture;
    tmpSurf = IMG_Load(texturePath);
    placeholder = SDL_CreateTextureFromSurface(renderer, tmpSurf);
    SDL_FreeSurface(tmpSurf);
}

void MenuItem :: setPlaceholderRect(int width, int height, int x, int y, int srcW, int srcH, int srcX, int srcY) {
    dstPlaceholderRect.w = width;
    dstPlaceholderRect.h = height;
    dstPlaceholderRect.x = x;
    dstPlaceholderRect.y = y;
    srcPlaceholderRect.w = 150;
    srcPlaceholderRect.h = 80;
    srcPlaceholderRect.x = 0;
    srcPlaceholderRect.y = 0;
}

void MenuItem :: setTextRect(TextInfo info) {
    dstTextRect.w = info.width;
    dstTextRect.h = info.height;
    dstTextRect.x = info.xPosition;
    dstTextRect.y = info.yPosition;
}

void MenuItem :: setTextRect(TextInfo info, int value1, int value2, const int xRw) {
    switch (xRw) {
        case CHANGE_XY_POSITION: {
            dstTextRect.w = info.width;
            dstTextRect.h = info.height;
            dstTextRect.x = value1;
            dstTextRect.y = value2;
            break;
        }
        case CHANGE_WIDTH_HEIGHT: {
            dstTextRect.w = value1;
            dstTextRect.h = value2;
            dstTextRect.x = info.xPosition;
            dstTextRect.y = info.yPosition;
            break;
        }
        default: {
            cout << "setRect//MenuItem error, exiting..." << endl;
            exit(0);
        }
    }
}

void MenuItem :: setTextRect(int width, int height, int x, int y) {
    dstTextRect.w = width;
    dstTextRect.h = height;
    dstTextRect.x = x;
    dstTextRect.y = y;
}

void Menu :: init(SDL_Renderer *renderer_, bool status) {
    if (!status) {
        isIntroActive = true;
        isIntroFaded = false;
        isMainMenuActive = false;
        textManager = new TextManager;
        for (int i = 0; i < 4; i++) {
            item[i] = new MenuItem;
            chapter[i] = new MenuItem;
        }
        title = new MenuItem;
        chapter[4] = new MenuItem;
    } else {
        isChainDone = false;
        isIntroActive = false;
        isIntroFaded = true;
        isMainMenuActive = true;
    }
    renderer = renderer_;
    temp_surf = NULL;
    color = { 255, 255, 255, 2 };
    intro = textManager -> renderText("Inspired by Helltaker...", "fonts/Travesty.ttf", color, 64, renderer);
    introFooter[0] = textManager -> renderText("By Gogolin Igor", "fonts/CaligulaDodgy.ttf", color, 18, renderer);
    introFooter[1] = textManager -> renderText("I506B", "fonts/CaligulaDodgy.ttf", color, 18, renderer);
    rectSet(intro, introRect);
    rectSet(introFooterR[0], 500, 650, introFooter[0].width, introFooter[0].height);
    rectSet(introFooterR[1], 500, 700, introFooter[1].width, introFooter[1].height);
    color = { 255, 255, 255, 255 };
    title -> init("MasterMind", "fonts/Travesty.ttf", WHITE, 110, "assets/placeholder.png", renderer);
    title -> setTextRect(title -> textInfo, title -> textInfo.xPosition, height + 150, CHANGE_XY_POSITION);
    title -> setPlaceholderRect(
        title -> dstTextRect.w + 150, title -> dstTextRect.h + 60, width / 2 - (title -> dstTextRect.w + 150) / 2, height + 90,
        150, 80, 0, 0);

    for (int i = 0; i < 4; i++) {
        string name;
        switch (i) {
            case 0: {
                name = "New Game";
                break;
            }
            case 1: {
                name = "Achievments";
                break;
            }
            case 2: {
                name = "Chapter Select";
                break;
            }
            case 3: {
                name = "Quit";
                break;
            }
        }
        item[i] -> init(name, "fonts/Leo Normal.ttf", WHITE, 32, "assets/placeholder-empty.png", renderer);
    }
    item[0] -> setTextRect(item[0] -> textInfo, width / 2 - 200, -300, CHANGE_XY_POSITION);
    item[1] -> setTextRect(item[1] -> textInfo, item[0] -> dstTextRect.x + 310, item[0] -> dstTextRect.y + 90, CHANGE_XY_POSITION);
    item[2] -> setTextRect(item[2] -> textInfo, item[1] -> dstTextRect.x - 400, item[1] -> dstTextRect.y + 90, CHANGE_XY_POSITION);
    item[3] -> setTextRect(item[3]  -> textInfo, item[2] -> dstTextRect.x + 450, item[2] -> dstTextRect.y + 90, CHANGE_XY_POSITION);
    for (int i = 0; i < 4; i++) {
        item[i] -> setPlaceholderRect(item[i] -> dstTextRect.w + 40, item[i] -> dstTextRect.h + 15, item[i] -> dstTextRect.x - 20, item[i] -> dstTextRect.y - 8, 0, 0, 0, 0);
    }
    temp_surf = IMG_Load("assets/chain.png");
    if (temp_surf == NULL) {
        cout << "Can't load image: " << endl;
    }
    chain[0] = SDL_CreateTextureFromSurface(renderer, temp_surf);
    if (chain[0] == NULL) {
        cout << "Can't create texture from surface: " << endl;
    }
    chainRect[0].w = 62;
    chainRect[0].h = height + 200;
    chainRect[0].x = width / 2 - chainRect[0].w / 2;
    chainRect[0].y = height - 20;
    SDL_FreeSurface(temp_surf);
    int xCounter = 107 - 768;
    int yCounter = height - 300;
    for (int i = 0; i < 5; i++) {

        string name = to_string(i + 1);
        chapter[i] -> init(name, "fonts/Leo Normal.ttf", WHITE, 32, "assets/placeholder-empty.png", renderer);
        chapter[i] -> setTextRect(chapter[i] -> textInfo, xCounter, yCounter, CHANGE_XY_POSITION);
        chapter[i] -> setPlaceholderRect(chapter[i] -> dstTextRect.w + 40, chapter[i] -> dstTextRect.h + 15, chapter[i] -> dstTextRect.x - 20, chapter[i] -> dstTextRect.y - 8, 0, 0, 0, 0);
        xCounter += 140;
        yCounter += 50;
        temp_surf = IMG_Load("assets/knot-hor.png");
        if (temp_surf == NULL) {
            cout << "Can't load image: " << endl;
        }
        chapterChain[i] = SDL_CreateTextureFromSurface(renderer, temp_surf);
        if (chapterChain[i] == NULL) {
            cout << "Can't create texture from surface: " << endl;
        }
        chapterChainRect[i].w = 768;
        chapterChainRect[i].h = 1;
        chapterChainRect[i].x = chapter[i] -> dstTextRect.x - 768;
        chapterChainRect[i].y = chapter[i] -> dstTextRect.y + 15;
        SDL_FreeSurface(temp_surf);
    }
//    int xCounter = 110;
//    int yCounter = height - 300;
//    for (int i = 0; i < 5; i++) {
//        string chapterName = to_string(i + 1);
//        chapter[i] = textManager -> renderText(chapterName, "fonts/Oswald-Regular.ttf", color, 32, renderer);
//        rectSet(chapter[i], chapterRect[i], xCounter , yCounter);
//        yCounter += 50;
//        xCounter += 700 / 5;
//    }

//    item[0] = textManager -> renderText("New game", "fonts/Oswald-Regular.ttf", color, 32, renderer);
//    rectSet(item[0], itemRect[0], width / 2 - 200, -300);
//    item[1] = textManager -> renderText("Continue", "fonts/Oswald-Regular.ttf", color, 32, renderer);
//    rectSet(item[1], itemRect[1], itemRect[0].x + 310 , itemRect[0].y + 90);
//    item[2] = textManager -> renderText("Chapter Select", "fonts/Oswald-Regular.ttf", color, 32, renderer);
//    rectSet(item[2], itemRect[2], itemRect[1].x - 400, itemRect[1].y + 90);
//    item[3] = textManager -> renderText("Quit", "fonts/Oswald-Regular.ttf", color, 32, renderer);
//    rectSet(item[3], itemRect[3], itemRect[2].x + 450, itemRect[2].y + 90);
//    temp_surf = IMG_Load("assets/placeholder.png");
//    placeHolder[0] = SDL_CreateTextureFromSurface(renderer, temp_surf);
//    rectSet(placeHolderRect[0], width / 2 - (titleRect.w + 150) / 2, height + 100, titleRect.w + 150, titleRect.h + 60);
//    SDL_FreeSurface(temp_surf);
    for (int i = 1; i < 5; i++) {
//        temp_surf = IMG_Load("assets/placeholder-empty.png");
//        placeHolder[i] = SDL_CreateTextureFromSurface(renderer, temp_surf);
//        rectSet(placeHolderRect[i], itemRect[i - 1].x - 20, itemRect[i - 1].y - 5, itemRect[i - 1].w + 40, itemRect[i - 1].h + 15);
        temp_surf = IMG_Load("assets/knot.png");
        chain[i] = SDL_CreateTextureFromSurface(renderer, temp_surf);
        rectSet(chainRect[i], item[i - 1] -> dstTextRect.x + item[i - 1] -> dstTextRect.w / 2, item[i - 1] -> dstTextRect.y - 1200, 1, 1200);
        SDL_FreeSurface(temp_surf);
    }
    temp_surf = IMG_Load("assets/background.png");
    background = SDL_CreateTextureFromSurface(renderer, temp_surf);
    rectSet(backgroundRect, 0, 0, 768, 768);
    SDL_FreeSurface(temp_surf);
    temp_surf = IMG_Load("assets/placeholder-active.png");
    item[menuActiveBtn] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
    chapter[chapterActiveBtn] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
    SDL_FreeSurface(temp_surf);
}

void Menu :: rectSet(TextInfo info, SDL_Rect &rect) {
    rect.x = info.xPosition;
	rect.y = info.yPosition;
	rect.w = info.width;
	rect.h = info.height;
}
void Menu :: rectSet(TextInfo info, SDL_Rect &rect, int x, int y) {
    rect.x = x;
	rect.y = y;
	rect.w = info.width;
	rect.h = info.height;
}

void Menu :: rectSet(SDL_Rect &rect, int x, int y, int w, int h) {
    rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}
void Menu :: update() {
    if (isIntroActive && static_cast<int>(intro.color.a) != 1) {
        int opacity = static_cast<int>(intro.color.a);
        if (opacity != 255) {
            isIntroFaded ? opacity-- : opacity++;
            intro.color.a = opacity;
            SDL_DestroyTexture(intro.texture);
            SDL_DestroyTexture(introFooter[0].texture);
            SDL_DestroyTexture(introFooter[1].texture);
            intro = textManager -> renderText("Inspired by Helltaker...", "fonts/Travesty.ttf", intro.color, 64, renderer);
            introFooter[0] = textManager -> renderText("By Gogolin Igor", "fonts/CaligulaDodgy.ttf", intro.color, 18, renderer);
            introFooter[1] = textManager -> renderText("I506B", "fonts/CaligulaDodgy.ttf", intro.color, 18, renderer);
            SDL_Delay(3);
        } else {
            isIntroFaded = true;
            SDL_Delay(1000);
            intro.color.a = --opacity;
            SDL_DestroyTexture(intro.texture);
            SDL_DestroyTexture(introFooter[0].texture);
            SDL_DestroyTexture(introFooter[1].texture);
            intro = textManager -> renderText("Inspired by Helltaker...", "fonts/Travesty.ttf", intro.color, 64, renderer);
            introFooter[0] = textManager -> renderText("By Gogolin Igor", "fonts/CaligulaDodgy.ttf", intro.color, 18, renderer);
            introFooter[1] = textManager -> renderText("I506B", "fonts/CaligulaDodgy.ttf", intro.color, 18, renderer);
        }
    } else if (isIntroActive && static_cast<int>(intro.color.a) == 1) {
        isIntroActive = false;
        isProfileActive = true;
        isMainMenuActive = false;
    } else if (isMainMenuActive) {
        if (isChapterSelectDone) {
            chapter[chapterStep] -> dstTextRect.x -= chapterSpeed;
            chapter[chapterStep] -> dstPlaceholderRect.x -= chapterSpeed;
            chapterChainRect[chapterStep].x -= chapterSpeed;
            sum += chapterSpeed;
            if (sum == 768) {
                sum = 0;
                chapterStep++;
            }
            if (chapterStep == 5) {
                isChapterSelectDone = false;
                chapterStep = 0;
            }
        } else if (!isChainDone) {
            if (chainRect[0].y != 0) {
                chainRect[0].y-=speed;
                title -> dstTextRect.y-=speed;
                title -> dstPlaceholderRect.y-=speed;
//                cout << title -> dstTextRect.y << endl;
//                cout << title -> dstPlaceholderRect.y << endl;
            } else {
                isChainDone = true;
            }
        } else {
//             int opacity = static_cast<int>(title.color.a);
//             if (opacity != 255) {
//                opacity++;
//                title.color.a = opacity;
//                title = textManager -> renderText("MasterMind", "fonts/Oswald-Regular.ttf", title.color, 128, renderer);
//            } else {
//                if (titleRect.y > 0 + 100) {
//                    titleRect.y-=2;
//                } else {
//                    isTitleDone = true;
//                }
//            }
            if (item[3] -> dstTextRect.y <= height - 100) {
                for (int i = 0; i < 4; i++) {
                    item[i] -> dstTextRect.y += speed;
                    item[i] -> dstPlaceholderRect.y+=speed;
                    chainRect[i + 1].y+=speed;
                }
            } else {
                isMenuDone = true;
            }
        }
    } else if (isChapterSelectActive) {
        if (!isChapterSelectDone) {
            chapter[chapterStep] -> dstTextRect.x += chapterSpeed;
            chapter[chapterStep] -> dstPlaceholderRect.x += chapterSpeed;
            chapterChainRect[chapterStep].x += chapterSpeed;
            sum += chapterSpeed;
            if (sum == 768) {
                sum = 0;
                chapterStep++;
            }
            if (chapterStep == 5) {
                isChapterSelectDone = true;
                chapterStep = 0;
            }
        }
        if (item[3] -> dstTextRect.y >= 0 - item[3] -> dstTextRect.h - 10) {
            for (int i = 0; i < 4; i++) {
                item[i] -> dstTextRect.y -=speed;
                item[i] -> dstPlaceholderRect.y-=speed;
                chainRect[i + 1].y-=speed;
            }
        }
    }
    //Cycle animation
//    time = SDL_GetTicks();
//    if(frame_last_changed + 50 > time) {
//        if(srcPlaceHolderRect[0].x == 750)
//        {
//            srcPlaceHolderRect[0].x = 0;
//        } else {
//            srcPlaceHolderRect[0].x += 150;
//        }
//        frame_last_changed = time;
//        SDL_Delay(1000/30);
//    }
   }
void Menu :: render() {
//    SDL_RenderCopy(renderer, background, NULL, &backgroundRect);
    if (isIntroActive) {
        SDL_RenderCopy(renderer, intro.texture, NULL, &introRect);
        SDL_RenderCopy(renderer, introFooter[0].texture, NULL, &introFooterR[0]);
        SDL_RenderCopy(renderer, introFooter[1].texture, NULL, &introFooterR[1]);
    } else if (isMainMenuActive) {
        SDL_RenderCopy(renderer, nameT.texture, NULL, &nameR);
        if (isChapterSelectDone) {
            SDL_RenderCopy(renderer, chain[0], NULL, &chainRect[0]);
            SDL_RenderCopy(renderer, title -> placeholder, &title -> srcPlaceholderRect, &title -> dstPlaceholderRect);
            SDL_RenderCopy(renderer, title -> text, NULL, &title -> dstTextRect);
            for (int i = 0; i < 5; i++) {
                SDL_RenderCopy(renderer, chapterChain[i], NULL, &chapterChainRect[i]);
                SDL_RenderCopy(renderer, chapter[i] -> placeholder, NULL, &chapter[i] -> dstPlaceholderRect);
                SDL_RenderCopy(renderer, chapter[i] -> text, NULL, &chapter[i] -> dstTextRect);
            }
        } else if (isTitleDone) {
            for (int i = 0; i < 4; i++) {
                SDL_RenderCopy(renderer, item[i] -> text, NULL, &item[i] -> dstTextRect);
            }
            SDL_RenderCopy(renderer, title -> text, NULL,  &title -> dstTextRect);
        } else if (!isChainDone) {
            SDL_RenderCopy(renderer, title -> placeholder, &title -> srcPlaceholderRect, &title -> dstPlaceholderRect);
            SDL_RenderCopy(renderer, title -> text, NULL, &title -> dstTextRect);
            SDL_RenderCopy(renderer, chain[0], NULL, &chainRect[0]);
            SDL_RenderCopy(renderer, title -> placeholder, &title -> srcPlaceholderRect, &title -> dstPlaceholderRect);
            SDL_RenderCopy(renderer, title -> text, NULL, &title -> dstTextRect);
        } else if (isChainDone) {
            for (int i = 3; i >= 0; i--) {
                SDL_RenderCopy(renderer, chain[i + 1], NULL, &chainRect[i + 1]);
                SDL_RenderCopy(renderer, item[i] -> placeholder ,NULL, &item[i] -> dstPlaceholderRect);
                SDL_RenderCopy(renderer, item[i] -> text, NULL, &item[i] -> dstTextRect);
            }
            SDL_RenderCopy(renderer, chain[0], NULL, &chainRect[0]);
            SDL_RenderCopy(renderer, title -> placeholder, &title -> srcPlaceholderRect, &title -> dstPlaceholderRect);
            SDL_RenderCopy(renderer, title -> text, NULL, &title -> dstTextRect);
        }
    } else if (isChapterSelectActive) {
        SDL_RenderCopy(renderer, nameT.texture, NULL, &nameR);
        for (int i = 3; i >= 0; i--) {
            SDL_RenderCopy(renderer, chain[i + 1], NULL, &chainRect[i + 1]);
            SDL_RenderCopy(renderer, item[i] -> placeholder ,NULL, &item[i] -> dstPlaceholderRect);
            SDL_RenderCopy(renderer, item[i] -> text, NULL, &item[i] -> dstTextRect);
        }
        SDL_RenderCopy(renderer, chain[0], NULL, &chainRect[0]);
        SDL_RenderCopy(renderer, title -> placeholder, &title -> srcPlaceholderRect, &title -> dstPlaceholderRect);
        SDL_RenderCopy(renderer, title -> text, NULL, &title -> dstTextRect);
        for (int i = 0; i < 5; i++) {
            SDL_RenderCopy(renderer, chapterChain[i], NULL, &chapterChainRect[i]);
            SDL_RenderCopy(renderer, chapter[i] -> placeholder, NULL, &chapter[i] -> dstPlaceholderRect);
            SDL_RenderCopy(renderer, chapter[i] -> text, NULL, &chapter[i] -> dstTextRect);
        }
    }
}
void Menu :: setChapterSelectActive(int active) {
    if (active == 0) {
        isMainMenuActive = false;
        isChapterSelectActive = true;
        isChapterSelectDone = false;
    } else {
        isMainMenuActive = true;
        isChapterSelectActive = false;
    }
}
int Menu :: getMenuActiveBtn() {
    return menuActiveBtn;
}

int Menu :: getChapterActiveBtn() {
    return chapterActiveBtn;
}

void Menu :: setMenuActiveBtn(int direction) {
    if (direction == 1) {
        menuActiveBtn++;
        if (menuActiveBtn != 4) {
            SDL_DestroyTexture(item[menuActiveBtn] -> placeholder);
            SDL_DestroyTexture(item[menuActiveBtn - 1] -> placeholder);
            temp_surf = IMG_Load("assets/placeholder-active.png");
            item[menuActiveBtn] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
            SDL_FreeSurface(temp_surf);
            temp_surf = IMG_Load("assets/placeholder-empty.png");
            item[menuActiveBtn - 1] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
            SDL_FreeSurface(temp_surf);
        } else {
            SDL_DestroyTexture(item[0] -> placeholder);
            SDL_DestroyTexture(item[3] -> placeholder);
            temp_surf = IMG_Load("assets/placeholder-active.png");
            item[0] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
            SDL_FreeSurface(temp_surf);
            temp_surf = IMG_Load("assets/placeholder-empty.png");
            item[3] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
            SDL_FreeSurface(temp_surf);
            menuActiveBtn = 0;
        }
    } else {
        menuActiveBtn--;
        if (menuActiveBtn != -1) {
            SDL_DestroyTexture(item[menuActiveBtn] -> placeholder);
            SDL_DestroyTexture(item[menuActiveBtn + 1] -> placeholder);
            temp_surf = IMG_Load("assets/placeholder-active.png");
            item[menuActiveBtn] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
            SDL_FreeSurface(temp_surf);
            temp_surf = IMG_Load("assets/placeholder-empty.png");
            item[menuActiveBtn + 1] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
            SDL_FreeSurface(temp_surf);
        } else {
            SDL_DestroyTexture(item[0] -> placeholder);
            SDL_DestroyTexture(item[3] -> placeholder);
            temp_surf = IMG_Load("assets/placeholder-active.png");
            item[3] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
            SDL_FreeSurface(temp_surf);
            temp_surf = IMG_Load("assets/placeholder-empty.png");
            item[0] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
            SDL_FreeSurface(temp_surf);
            menuActiveBtn = 3;
        }
    }
}

void Menu :: setChapterActiveBtn(int direction) {
    if (lastPassedLevel == 1) {
        return;
    }
    if (isChapterSelectDone) {
        if (direction == 1) {
            chapterActiveBtn++;
            if (chapterActiveBtn != lastPassedLevel) {
                SDL_DestroyTexture(chapter[chapterActiveBtn] -> placeholder);
                SDL_DestroyTexture(chapter[chapterActiveBtn - 1] -> placeholder);
                temp_surf = IMG_Load("assets/placeholder-active.png");
                chapter[chapterActiveBtn] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
                SDL_FreeSurface(temp_surf);
                temp_surf = IMG_Load("assets/placeholder-empty.png");
                chapter[chapterActiveBtn - 1] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
                SDL_FreeSurface(temp_surf);
            } else {
                SDL_DestroyTexture(chapter[lastPassedLevel - 1] -> placeholder);
                SDL_DestroyTexture(chapter[0] -> placeholder);
                temp_surf = IMG_Load("assets/placeholder-active.png");
                chapter[0] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
                SDL_FreeSurface(temp_surf);
                temp_surf = IMG_Load("assets/placeholder-empty.png");
                chapter[lastPassedLevel - 1] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
                SDL_FreeSurface(temp_surf);
                chapterActiveBtn = 0;
            }
        } else {
            chapterActiveBtn--;
            if (chapterActiveBtn != -1) {
                SDL_DestroyTexture(chapter[chapterActiveBtn] -> placeholder);
                SDL_DestroyTexture(chapter[chapterActiveBtn + 1] -> placeholder);
                temp_surf = IMG_Load("assets/placeholder-active.png");
                chapter[chapterActiveBtn] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
                SDL_FreeSurface(temp_surf);
                temp_surf = IMG_Load("assets/placeholder-empty.png");
                chapter[chapterActiveBtn + 1] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
                SDL_FreeSurface(temp_surf);
            } else {
                SDL_DestroyTexture(chapter[lastPassedLevel - 1] -> placeholder);
                SDL_DestroyTexture(chapter[0] -> placeholder);
                temp_surf = IMG_Load("assets/placeholder-active.png");
                chapter[lastPassedLevel - 1] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
                SDL_FreeSurface(temp_surf);
                temp_surf = IMG_Load("assets/placeholder-empty.png");
                chapter[0] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
                SDL_FreeSurface(temp_surf);
                chapterActiveBtn = lastPassedLevel - 1;
            }
        }
    }
}

bool Menu :: getMenuActive() {
    return isMainMenuActive;
}

void Menu :: setMenuActive(bool status) {
    isMainMenuActive = status;
}

bool Menu :: getChapterSelectActive() {
    return isChapterSelectActive;
}

bool Menu :: getChapterSelectDone() {
    return isChapterSelectDone;
}

void Menu :: createHello(string name) {
    nameT = textManager -> renderText("Profile:  " + name, "fonts/CaligulaDodgy.ttf", {0, 255, 0, 255}, 24, renderer);
    rectSet(nameR, 15, 770, nameT.width, nameT.height);
}

void Menu :: setLastPassedLevel(int level) {
    lastPassedLevel = level;
    if (lastPassedLevel != 5) {
        for (int i = 1; i < lastPassedLevel; i++) {
            SDL_DestroyTexture(chapter[i] -> placeholder);
            temp_surf = IMG_Load("assets/placeholder-empty.png");
            chapter[i] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
            SDL_FreeSurface(temp_surf);
        }
        for (int i = lastPassedLevel; i < 5; i++) {
            SDL_DestroyTexture(chapter[i] -> placeholder);
            temp_surf = IMG_Load("assets/placeholder-blocked.png");
            chapter[i] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
            SDL_FreeSurface(temp_surf);
        }
    } else {
         for (int i = 1; i < 5; i++) {
            SDL_DestroyTexture(chapter[i] -> placeholder);
            temp_surf = IMG_Load("assets/placeholder-empty.png");
            chapter[i] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
            SDL_FreeSurface(temp_surf);
        }
    }
}

void Menu :: setZero() {
    SDL_DestroyTexture(item[menuActiveBtn] -> placeholder);
    SDL_DestroyTexture(chapter[chapterActiveBtn] -> placeholder);
    temp_surf = IMG_Load("assets/placeholder-empty.png");
    item[menuActiveBtn] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
    chapter[chapterActiveBtn] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
    SDL_FreeSurface(temp_surf);
    menuActiveBtn = 0;
    chapterActiveBtn = 0;
    temp_surf = IMG_Load("assets/placeholder-active.png");
    item[menuActiveBtn] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
    chapter[chapterActiveBtn] -> placeholder = SDL_CreateTextureFromSurface(renderer, temp_surf);
    SDL_FreeSurface(temp_surf);
    isMenuDone = false;
    isBtnChosen = false;
    isChainDone = false;
    isIntroActive = false;
    isIntroFaded = true;
    isMainMenuActive = true;
    isChapterSelectActive = false;
    isChapterSelectDone = false;
    rectSet(intro, introRect);
    rectSet(introFooterR[0], 500, 650, introFooter[0].width, introFooter[0].height);
    rectSet(introFooterR[1], 500, 700, introFooter[1].width, introFooter[1].height);
    title -> setTextRect(title -> textInfo, title -> textInfo.xPosition, height + 150, CHANGE_XY_POSITION);
    title -> setPlaceholderRect(
    title -> dstTextRect.w + 150, title -> dstTextRect.h + 60, width / 2 - (title -> dstTextRect.w + 150) / 2, height + 90,
        150, 80, 0, 0);
    item[0] -> setTextRect(item[0] -> textInfo, width / 2 - 200, -300, CHANGE_XY_POSITION);
    item[1] -> setTextRect(item[1] -> textInfo, item[0] -> dstTextRect.x + 310, item[0] -> dstTextRect.y + 90, CHANGE_XY_POSITION);
    item[2] -> setTextRect(item[2] -> textInfo, item[1] -> dstTextRect.x - 400, item[1] -> dstTextRect.y + 90, CHANGE_XY_POSITION);
    item[3] -> setTextRect(item[3]  -> textInfo, item[2] -> dstTextRect.x + 450, item[2] -> dstTextRect.y + 90, CHANGE_XY_POSITION);
    for (int i = 1; i < 5; i++) {
        rectSet(chainRect[i], item[i - 1] -> dstTextRect.x + item[i - 1] -> dstTextRect.w / 2, item[i - 1] -> dstTextRect.y - 1200, 1, 1200);
    }
    for (int i = 0; i < 4; i++) {
        item[i] -> setPlaceholderRect(item[i] -> dstTextRect.w + 40, item[i] -> dstTextRect.h + 15, item[i] -> dstTextRect.x - 20, item[i] -> dstTextRect.y - 8, 0, 0, 0, 0);
    }
    int xCounter = 107 - 768;
    int yCounter = height - 300;
    chainRect[0].w = 62;
    chainRect[0].h = height + 200;
    chainRect[0].x = width / 2 - chainRect[0].w / 2;
    chainRect[0].y = height - 20;
    for (int i = 0; i < 5; i++) {
        chapter[i] -> setTextRect(chapter[i] -> textInfo, xCounter, yCounter, CHANGE_XY_POSITION);
        chapter[i] -> setPlaceholderRect(chapter[i] -> dstTextRect.w + 40, chapter[i] -> dstTextRect.h + 15, chapter[i] -> dstTextRect.x - 20, chapter[i] -> dstTextRect.y - 8, 0, 0, 0, 0);
        xCounter += 140;
        yCounter += 50;
        chapterChainRect[i].w = 768;
        chapterChainRect[i].h = 1;
        chapterChainRect[i].x = chapter[i] -> dstTextRect.x - 768;
        chapterChainRect[i].y = chapter[i] -> dstTextRect.y + 15;
    }
}

void Menu :: destroy() {
    for (int i = 0 ; i < 5; i++) {
        SDL_DestroyTexture(chain[i]);
        SDL_DestroyTexture(chapterChain[i]);
    }
    for (int i = 0; i < 4; i++) {
        SDL_DestroyTexture(item[i] -> text);
        SDL_DestroyTexture(item[i] -> placeholder);
        SDL_DestroyTexture(chapter[i] -> text);
        SDL_DestroyTexture(chapter[i] -> placeholder);
    }
    SDL_DestroyTexture(title -> text);
    SDL_DestroyTexture(title -> placeholder);
    SDL_DestroyTexture(chapter[4] -> text);
    SDL_DestroyTexture(chapter[4] -> placeholder);
    SDL_DestroyTexture(intro.texture);
    SDL_DestroyTexture(introFooter[0].texture);
    SDL_DestroyTexture(introFooter[1].texture);
    SDL_DestroyTexture(nameT.texture);
}

int Menu :: getLastPassedLevel() {
    return lastPassedLevel;
}


