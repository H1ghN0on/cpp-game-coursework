#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "TextManager.h"
#include "FileManager.h"
#include "Menu.h"
#include "Rules.h"
#include "Profile.h"
#include "Map.h"
#include "Player.h"
#include "Achievements.h"

//Singletone
class Achievements;
class FileManager;
class StepController;
class Game {
private:
    bool isRunning = false;
	bool isMenuActive = true;
	bool isRulesActive = false;
	bool isEnterName = false;
	bool isGameActive = false;
	bool isAchievementsActive = false;

	int activeLevel;
    int textureSize = 64;
    int moving = 0;

    Menu *menu = new Menu;
    Rules *rules = new Rules;
    Profile *profile = new Profile;
    Achievements *achieve = new Achievements;
    Map *map = new Map;
    Player *player = new Player;
    FileManager *fileManager = new FileManager;
    LevelInfo *levelInfo = new LevelInfo;
    GameObject *gameObject = NULL;
    StepController *stepController = NULL;

    SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

    void setLevel(int number);

    //Запрет доступа к классу (синглтон)
    Game();
	~Game();
	Game(Game const&);
	Game& operator= (Game const&);

public:
    string name;
    static Game& instance();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();
};

#endif // GAME_H_INCLUDED
