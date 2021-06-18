#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "SDL2/SDL.h"
#include "TextManager.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "Menu.h"
#include "Rules.h"
#include "Profile.h"
#include "Map.h"
#include "Player.h"
#include "FileManager.h"
//Singletone
class FileManager;
class StepController;
class Game {
private:
    bool isRunning = false;
	bool isMenuActive = true;
	bool isRulesActive = false;
	bool isEnterName = false;
	bool isGameActive = false;
	int activeLevel;
    Menu *menu = NULL;
    Rules *rules = NULL;
    Profile *profile = NULL;
    int textureSize = 64;
    int moving = 0;
    Map *map = NULL;
    Player *player = NULL;
    GameObject *gameObject = NULL;
	bool isPressed = false;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
    Game();
	~Game();
	Game(Game const&);
	Game& operator= (Game const&);
    StepController *stepController = NULL;
    FileManager *fileManager = new FileManager;
    LevelInfo *levelInfo = new LevelInfo;
    void setLevel(int number);
    int levelNumber;

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
