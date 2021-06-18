#ifndef PROFILE_H_INCLUDED
#define PROFILE_H_INCLUDED

#include <iterator>
#include <iostream>
#include <vector>
#include "TextManager.h"
#include <fstream>
using namespace std;

class PlayerInfo {
public:
    string name;
    int lastPassedLevel;
};

class Profile {
private:
    SDL_Color color = {255, 255, 255, 0};
    int index = 0;
    int playerSize = 0;
    bool isEntered = false;
    vector<PlayerInfo> players;
    SDL_Renderer *renderer;
    TextManager textManager;
    TextInfo text, correct, alert[2], nameCorrect;
    SDL_Rect textR, correctR, alertR[2], nameCorrectR;
    string name = "..............";
public:
    bool isAlertExists = false;
    void init(SDL_Renderer *renderer);
    void enter(char c);
    void enter();
    void render();
    bool checkExistance();
    void addPlayer();
    void saveFile();
    void newPlayerAlert();
    void oldPlayerAlert();
    int getLastPassedLevel();
    string getName();
    void destroy();
    void setLastPassedLevel();
    void setLastPassedLevel(int level);
    void setIsEntered();
    bool getIsEntered();
    bool checkEnter();
};

#endif // PROFILE_H_INCLUDED
