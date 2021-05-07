#include "Game.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "Map.h"
#include "GameObject.h"
#include "StepController.h"
void Game :: init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flag = 0;
	if (fullscreen) {
		flag = SDL_WINDOW_FULLSCREEN;
	}
	if (!SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cout << "SDL initialized..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
		if (window) {
			std::cout << "Window created..." << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			std::cout << "Renderer created..." << std::endl;
		}
		isRunning = true;
		std::cout << "Game is running..." << std::endl;
	} else {
		isRunning = false;
		std::cout << "Error..." << std::endl;
	}
	map = new Map;
    gameObject = new GameObject(renderer);
    player = new Player;
	map -> init(renderer);
	gameObject -> setMap(map -> getMap());
	map -> draw();
    player -> init();
}

void Game :: handleEvents() {
    if (isPressed) {
        return;
	}
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN: {
		    switch (event.key.keysym.sym) {
		        case SDLK_UP: {
                    player -> moveTo(1);
                    return;
                }
                case SDLK_RIGHT: {
                    player -> moveTo(2);
                    return;
                }
                case SDLK_DOWN: {
                    player -> moveTo(3);
                    return;
                }
                case SDLK_LEFT: {
                    player -> moveTo(4);
                    return;
                }
		    }
		    break;
		}
	}
}

void Game :: update() {
    player -> update();
    map -> update();
    if (stepController -> getStep() == 0) {
        stepController -> setStep(20);
    }

}
void Game :: render() {
    SDL_SetRenderDrawColor(renderer, 104, 0, 100, 255);
    SDL_RenderClear(renderer);
    map -> render();
    player -> render();
	SDL_RenderPresent(renderer);
}

void Game :: clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Finished Successful..." << std::endl;
}

bool Game :: running() {
	return isRunning;
}

//---------------------------------------Singletone------------------------------------//
Game :: Game() {

}

Game :: ~Game() {

}

Game& Game :: instance() {
    static Game s;
    return s;
}
