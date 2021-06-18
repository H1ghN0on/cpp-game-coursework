#include "Game.h"
#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "Map.h"
#include "GameObject.h"
#include "FileManager.h"
#include "StepController.h"
#include "LevelInfo.h"
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
		if (TTF_Init() == 0) {
            std :: cout << "TTF initialized" << std :: endl;
		}
		if (!IMG_Init(IMG_INIT_PNG)) {
            cout << "is nice" << endl;
		}
	} else {
		isRunning = false;
		std::cout << "Error..." << std::endl;
	}
    fileManager -> readFile("level1");
	map = new Map;
    gameObject = new GameObject(renderer, textureSize);
    player = new Player;
    stepController = new StepController(renderer);
    profile = new Profile;
    profile -> init(renderer);
	map -> init(renderer, textureSize);
	gameObject -> setMap(map -> getMap());
	map -> draw();
    player -> init(stepController, profile);
    player -> setPosition(levelInfo -> strPosition, levelInfo -> colPosition);
    levelNumber = 1;
    menu = new Menu;
    menu -> init(renderer, false);
    rules = new Rules;
    rules -> init(renderer);
}

void Game :: handleEvents() {
    if (isPressed) {
        return;
	}
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.key.repeat == 0) {
        int menuBtn = menu -> getMenuActiveBtn();
        int chapterBtn = menu -> getChapterActiveBtn();
	    if (isGameActive) {
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
                        case SDLK_ESCAPE: {
                            isGameActive = false;
                            isRulesActive = false;
                            isMenuActive = true;
                        }
                        case SDLK_r: {
                            setLevel(activeLevel);
                        }
                    }
                    break;
                }
            }
        } else if (menu -> isProfileActive) {
            switch (event.type) {
                case SDL_QUIT: {
                    isRunning = false;
                    break;
                }
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            profile -> enter();
                            break;
                        }
                        case SDLK_ESCAPE: {
                            isRulesActive = false;
                            break;
                        }
                        case SDLK_RETURN: {
                            if (!profile -> isAlertExists) {
                                if (profile -> checkEnter()) {
                                    if (!profile -> checkExistance()) {
                                        profile -> addPlayer();
                                        profile -> saveFile();
                                        profile -> newPlayerAlert();
                                        cout << "new player" << endl;
                                    } else {
                                        cout << "old player" << endl;
                                        profile -> oldPlayerAlert();
                                    }
                                    menu -> createHello(profile -> getName());
                                    menu -> setLastPassedLevel(profile -> getLastPassedLevel());
                                    profile -> setIsEntered();
                                } else {
                                    break;
                                }
                            } else {
                                profile -> isAlertExists = false;
                                profile -> destroy();
                                menu -> isProfileActive = false;
                                menu -> isMainMenuActive = true;
                            }
                            break;
                        }
                        default: {
                            if (!profile -> getIsEntered()) {
                                profile -> enter(event.key.keysym.sym);
                            }
                            break;
                        }
                    }
                }
	        }
        } else if (menu -> getMenuActive() && menu -> isMenuDone) {
            switch (event.type) {
                case SDL_QUIT: {
                    isRunning = false;
                    break;
                }
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP: {
                            menu -> setMenuActiveBtn(0);
                            break;
                        }
                        case SDLK_DOWN: {
                            menu -> setMenuActiveBtn(1);
                            break;
                        }
                        case SDLK_RETURN: {
                            if (menu -> getMenuActive() && !menu -> getChapterSelectDone()) {
                                switch (menuBtn) {
                                    case 0: {
                                        isRulesActive = true;
                                        menu -> setMenuActive(false);
                                        break;
                                    }
                                    case 2: {
                                        menu -> setChapterSelectActive(0);
                                        break;
                                    }
                                    case 3: {
                                        isRunning = false;
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
	        }
        } else if (menu -> getChapterSelectActive()) {
            switch (event.type) {
                case SDL_QUIT: {
                    isRunning = false;
                    break;
                }
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT: {
                            menu -> setChapterActiveBtn(0);
                            break;
                        }
                        case SDLK_RIGHT: {
                            menu -> setChapterActiveBtn(1);
                            break;
                        }
                        case SDLK_ESCAPE: {
                            if (!!menu -> getChapterSelectDone()) {
                                menu -> setChapterSelectActive(1);
                                menu -> isMenuDone = false;
                            }
                            break;
                        }
                        case SDLK_RETURN: {
                            if (menu -> getChapterSelectActive()) {
                                switch (chapterBtn) {
                                    case 0: {
                                        cout << "Выбран уровень 1" << endl;
                                        setLevel(1);
                                        menu -> setMenuActive(false);
                                        isMenuActive = false;
                                        isGameActive = true;
                                        menu -> setZero();
                                        break;
                                    }
                                    case 1: {
                                        cout << "Выбран уровень 2" << endl;
                                        setLevel(2);
                                        menu -> setMenuActive(false);
                                        isMenuActive = false;
                                        isGameActive = true;
                                        menu -> setZero();
                                        break;
                                    }
                                    case 2: {
                                        cout << "Выбран уровень 3" << endl;
                                        setLevel(3);
                                        menu -> setMenuActive(false);
                                        isMenuActive = false;
                                        isGameActive = true;
                                        menu -> setZero();
                                        break;
                                    }
                                    case 3: {
                                        cout << "Выбран уровень 4" << endl;
                                        setLevel(4);
                                        menu -> setMenuActive(false);
                                        isMenuActive = false;
                                        isGameActive = true;
                                        menu -> setZero();
                                        break;
                                    }
                                    case 4: {
                                        cout << "Выбран уровень 5" << endl;
                                        menu -> setMenuActive(false);
                                        isMenuActive = false;
                                        isGameActive = true;
                                        setLevel(5);
                                        menu -> setZero();
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (isRulesActive) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_RETURN: {
                            isGameActive = true;
                            isRulesActive = false;
                            menu -> setZero();
                            setLevel(1);
                            break;
                        }
                    }
                    break;
                }
            }
        }
	}
}

void Game :: update() {
    if (isGameActive) {
        player -> update();
        map -> update();
        if (stepController -> getStep() <= -1) {
            setLevel(activeLevel);
        }
    } else if (isRulesActive) {
        rules -> update();
    } else if (isMenuActive) {
        menu -> update();
    }
}
void Game :: render() {
    SDL_RenderClear(renderer);
    if (isGameActive) {
        SDL_SetRenderDrawColor(renderer, 104, 0, 100, 255);
        map -> render();
        player -> render();
        stepController -> render();
    } else if (menu -> isProfileActive) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        profile -> render();
    } else if (isRulesActive) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        rules -> render();
    } else if (isMenuActive) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        menu -> render();
    }
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

void Game :: setLevel(int level) {
    std :: string filename = "level";
    filename.insert(5, std :: to_string(level));
    stepController -> destroy();
    if (!fileManager -> readFile(filename)) {
        stepController -> setStep(levelInfo -> step, renderer, level);
        return;
    };
    map -> destroy();
    player -> destroy();
    map -> init(renderer, textureSize);
    gameObject -> setMap(map -> getMap());
    map -> draw();
    player -> setPosition(levelInfo -> strPosition, levelInfo -> colPosition);
    stepController -> setStep(levelInfo -> step, renderer, level);
    activeLevel = level;
}
