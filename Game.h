#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "SDL2/SDL.h"
#include "Map.h"
#include "Player.h"
//Singletone

class Game {
private:
    int moving = 0;
    Map *map = new Map;
    Player *player = new Player;
    GameObject *gameObject;
	bool isRunning = false;
	bool isPressed = false;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
    Game();
	~Game();
	Game(Game const&);
	Game& operator= (Game const&);

public:
    static Game& instance();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();
};

#endif // GAME_H_INCLUDED
