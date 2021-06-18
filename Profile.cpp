#include "Profile.h"

void Profile :: init(SDL_Renderer *renderer_) {
    renderer = renderer_;
    nameCorrect = textManager.renderText("Enter your name:" ,"fonts/CaligulaDodgy.ttf", {255, 255, 255, 255}, 32, renderer);
    nameCorrectR.w = nameCorrect.width;
    nameCorrectR.h = nameCorrect.height;
    nameCorrectR.x = 20;
    nameCorrectR.y = 375;
    text = textManager.renderText(name, "fonts/CaligulaDodgy.ttf", {255, 255, 255, 255}, 32, renderer);
    alertR[0].x = 15;
    alertR[0].y = 475;
    alertR[1].x = 15;
    alertR[1].y = 525;
    textR.x = 400;
    textR.y = 375;
    textR.w = text.width;
    textR.h = text.height;
    correct = textManager.renderText(" ", "fonts/CaligulaDodgy.ttf", {255, 0, 0, 255}, 32, renderer);
    correctR.x = 15;
    correctR.y = 425;
    correctR.w = correct.width;
    correctR.h = correct.height;
    ifstream out("players.txt");
    out >> playerSize;
    for (int i = 0; i < playerSize; i++) {
        PlayerInfo tmp;
        out >> tmp.name;
        out >> tmp.lastPassedLevel;
        players.push_back(tmp);
    }
    out.close();
    name = "";
}



void Profile :: enter(char c) {
    if (c < '0' || c > '9' && c < 'a' || c > 'z') {
        SDL_DestroyTexture(correct.texture);
        correct = textManager.renderText("Incorrect symbol", "fonts/CaligulaDodgy.ttf", {255, 0, 0, 255}, 32, renderer);
        correctR.w = correct.width;
    } else if (name.length() <= 10) {
        name.push_back(c);
        SDL_DestroyTexture(correct.texture);
        correct = textManager.renderText("", "fonts/CaligulaDodgy.ttf", {255, 0, 0, 255}, 32, renderer);
        correctR.w = correct.width;
    } else {
        SDL_DestroyTexture(correct.texture);
        correct = textManager.renderText("Too much symbols", "fonts/CaligulaDodgy.ttf", {255, 0, 0, 255}, 32, renderer);
        correctR.w = correct.width;
    }
    SDL_DestroyTexture(text.texture);
    text = textManager.renderText(name, "fonts/CaligulaDodgy.ttf", {255, 255, 255, 255}, 32, renderer);
    textR.w = text.width;
}

void Profile :: enter() {
    if (!name.empty()) {
        name.pop_back();
        SDL_DestroyTexture(correct.texture);
        correct = textManager.renderText(" ", "fonts/CaligulaDodgy.ttf", {255, 0, 0, 255}, 32, renderer);
        correctR.w = correct.width;
    }
    SDL_DestroyTexture(text.texture);
    text = textManager.renderText(name, "fonts/CaligulaDodgy.ttf", {255, 255, 255, 255}, 32, renderer);
    textR.w = text.width;
}

void Profile :: render() {
    SDL_RenderCopy(renderer, nameCorrect.texture, NULL, &nameCorrectR);
    SDL_RenderCopy(renderer, text.texture, NULL, &textR);
    SDL_RenderCopy(renderer, correct.texture, NULL, &correctR);
    if (isAlertExists) {
        SDL_RenderCopy(renderer, alert[0].texture, NULL, &alertR[0]);
        SDL_RenderCopy(renderer, alert[1].texture, NULL, &alertR[1]);
    }
}

bool Profile :: checkExistance() {
    for (int i = 0; i < playerSize; i++) {
        if (players[i].name == name) {
            index = i;
            return true;
        }
    }
    return false;
}

bool Profile :: checkEnter() {
    if (name == ".............." || name.empty()) {
        SDL_DestroyTexture(correct.texture);
        correct = textManager.renderText("Enter something", "fonts/CaligulaDodgy.ttf", {255, 0, 0, 255}, 32, renderer);
        correctR.w = correct.width;
        return false;
    }
    return true;
}

void Profile :: addPlayer() {
    PlayerInfo player;
    player.lastPassedLevel = 1;
    player.name = name;
    playerSize++;
    index = playerSize - 1;
    players.push_back(player);
}

void Profile :: saveFile() {
    ofstream in("players.txt");//подключение текстового файла для записи в бинарном режиме
    in << playerSize << endl;
    for (int i = 0; i < playerSize; i++) {
        in << players[i].name << " " << players[i].lastPassedLevel << endl;
    }
    cout << playerSize << endl;
    in.close();//закрываем файл
}

void Profile :: newPlayerAlert() {
    string alertName = "Welcome, " + name ;
    alert[0] = textManager.renderText(alertName, "fonts/CaligulaDodgy.ttf", {0, 255, 0, 255}, 32, renderer);
    alertR[0].w = alert[0].width;
    alertR[0].h = alert[0].height;
    alert[1] = textManager.renderText("Press Enter to continue...", "fonts/CaligulaDodgy.ttf", {0, 255, 0, 255}, 24, renderer);
    alertR[1].w = alert[1].width;
    alertR[1].h = alert[1].height;
    isAlertExists = true;
}

void Profile :: oldPlayerAlert() {
    string alertName = "Welcome back, " + name ;
    alert[0] = textManager.renderText(alertName, "fonts/CaligulaDodgy.ttf", {0, 255, 0, 255}, 32, renderer);
    alertR[0].w = alert[0].width;
    alertR[0].h = alert[0].height;
    alert[1] = textManager.renderText("Press Enter to continue...", "fonts/CaligulaDodgy.ttf", {0, 255, 0, 255}, 24, renderer);
    alertR[1].w = alert[1].width;
    alertR[1].h = alert[1].height;
    isAlertExists = true;
}

string Profile :: getName() {
    return name;
}

int Profile :: getLastPassedLevel() {
    return players[index].lastPassedLevel;
}

void Profile :: setLastPassedLevel() {
    players[index].lastPassedLevel++;
}

void Profile :: destroy() {
    SDL_DestroyTexture(text.texture);
    SDL_DestroyTexture(correct.texture);
    SDL_DestroyTexture(nameCorrect.texture);
    SDL_DestroyTexture(alert[0].texture);
    SDL_DestroyTexture(alert[1].texture);
}

bool Profile :: getIsEntered() {
    return isEntered;
}

void Profile :: setIsEntered() {
    isEntered = true;
}
