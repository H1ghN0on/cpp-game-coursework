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
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
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

    gameObject = new GameObject(renderer, textureSize);
    stepController = new StepController(renderer);

    profile -> init(renderer);
    menu -> init(renderer, false);
    rules -> init(renderer);

	map -> init(renderer, textureSize);
    gameObject -> setMap(map -> getMap());
    map -> draw();

    player -> init(stepController, profile);
    player -> setPosition(levelInfo -> strPosition, levelInfo -> colPosition);
}

void Game :: handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.key.repeat == 0) {
        switch (event.type) {
            case SDL_QUIT: {
                isRunning = false;
                break;
            }
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_UP: {
                        if (isGameActive) {
                            player -> moveTo(1);
                        } else if (menu -> getMenuActive() && menu -> isMenuDone) {
                            menu -> setMenuActiveBtn(0);
                        }
                        break;
                    }
                    case SDLK_RIGHT: {
                        if (isGameActive) {
                            player -> moveTo(2);
                        } else if (menu -> getChapterSelectActive() && menu -> getChapterSelectDone()) {
                            menu -> setChapterActiveBtn(1);
                        }
                        break;
                    }
                    case SDLK_DOWN: {
                        if (isGameActive) {
                            player -> moveTo(3);
                        } else if (menu -> getMenuActive() && menu -> isMenuDone) {
                            menu -> setMenuActiveBtn(1);
                        }
                        break;
                    }
                    case SDLK_LEFT: {
                        if (isGameActive) {
                            player -> moveTo(4);
                        } else if (menu -> getChapterSelectActive() && menu -> getChapterSelectDone()) {
                            menu -> setChapterActiveBtn(0);
                        }
                        break;
                    }
                    case SDLK_ESCAPE: {
                        if (isGameActive) {
                            isGameActive = false;
                            isRulesActive = false;
                            isMenuActive = true;
                        } else if (menu -> getChapterSelectActive() && menu -> getChapterSelectDone()) {
                            menu -> setChapterSelectActive(1);
                            menu -> isMenuDone = false;
                        } else if (isAchievementsActive) {
                            isAchievementsActive = false;
                            menu -> setMenuActive(true);
                        }
                        break;
                    }
                    case SDLK_RETURN: {
                        if (menu -> getMenuActive() && menu -> isMenuDone && !menu -> getChapterSelectDone()) {
                            switch (menu -> getMenuActiveBtn()) {
                                case 0: {
                                    isRulesActive = true;
                                    menu -> setMenuActive(false);
                                    break;
                                }
                                case 1: {
                                    isAchievementsActive = true;
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
                        } else if (menu -> getChapterSelectActive() && menu -> getChapterSelectDone()) {
                            switch (menu -> getChapterActiveBtn()) {
                                case 0: {
                                    setLevel(1);
                                    menu -> setMenuActive(false);
                                    isMenuActive = false;
                                    isGameActive = true;
                                        menu -> setZero();
                                    break;
                                }
                                case 1: {
                                    setLevel(2);
                                    menu -> setMenuActive(false);
                                    isMenuActive = false;
                                    isGameActive = true;
                                    menu -> setZero();
                                    break;
                                }
                                case 2: {
                                    setLevel(3);
                                    menu -> setMenuActive(false);
                                    isMenuActive = false;
                                    isGameActive = true;
                                    menu -> setZero();
                                    break;
                                }
                                case 3: {
                                    setLevel(4);
                                    menu -> setMenuActive(false);
                                    isMenuActive = false;
                                    isGameActive = true;
                                    menu -> setZero();
                                    break;
                                }
                                case 4: {
                                    setLevel(5);
                                    menu -> setMenuActive(false);
                                    isMenuActive = false;
                                    isGameActive = true;
                                    menu -> setZero();
                                    break;
                                }
                            }
                        } else if (menu -> isProfileActive) {
                            if (!profile -> isAlertExists) {
                                if (profile -> checkEnter()) {
                                    if (!profile -> checkExistance()) {
                                        profile -> addPlayer();
                                        profile -> saveFile();
                                        profile -> newPlayerAlert();
                                    } else {
                                        profile -> oldPlayerAlert();
                                    }
                                    menu -> createHello(profile -> getName());
                                    menu -> setLastPassedLevel(profile -> getLastPassedLevel());
                                    profile -> setIsEntered();
                                    achieve -> init(renderer, profile -> getAchievementLevel());
                                }
                            } else {
                                profile -> isAlertExists = false;
                                profile -> destroy();
                                menu -> isProfileActive = false;
                                menu -> isMainMenuActive = true;
                            }
                        } else if (isRulesActive) {
                            isGameActive = true;
                            isRulesActive = false;
                            menu -> setZero();
                            setLevel(1);
                            profile -> setLastPassedLevel(1);
                            profile -> saveFile();
                            menu -> setLastPassedLevel(1);
                        }
                        break;
                    }
                    case SDLK_r: {
                        if (isGameActive) {
                            setLevel(activeLevel);
                        } else if (!profile -> getIsEntered()) {
                            profile -> enter(event.key.keysym.sym);
                        }
                        break;
                    }
                    case SDLK_BACKSPACE: {
                        profile -> enter();
                        break;
                    }
                    default: {
                        if (!profile -> getIsEntered()) {
                            profile -> enter(event.key.keysym.sym);
                        }
                        break;
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
            if (player -> getIsLevelPassed()) {
                player -> setIsLevelPassed(false);
                if (activeLevel < 5) {
                    if (activeLevel >= menu -> getLastPassedLevel()) {
                        menu -> setLastPassedLevel(activeLevel + 1);
                        if (activeLevel >= profile -> getAchievementLevel()) {
                            profile -> setAchievementLevel(activeLevel);
                            achieve -> update(activeLevel);
                            profile -> saveFile();
                        }
                    }
                    setLevel(++activeLevel);
                } else {
                    profile -> setAchievementLevel(activeLevel);
                    achieve -> update(activeLevel);
                    profile -> saveFile();
                    isGameActive = false;
                    isRulesActive = false;
                    isMenuActive = true;
                }
            } else {
                setLevel(activeLevel);
            }
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
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        if (menu -> isProfileActive) {
            profile -> render();
        } else if (isRulesActive) {
            rules -> render();
        } else if (isAchievementsActive) {
            achieve -> render();
        } else if (isMenuActive) {
            menu -> render();
        }
    }
	SDL_RenderPresent(renderer);
}

void Game :: setLevel(int level) {
    std :: string filename = "level";
    filename.insert(5, std :: to_string(level));
    stepController -> destroy();
    if (!fileManager -> readFile(filename)) {
        activeLevel = level;
        stepController -> setStep(levelInfo -> step, level);
        return;
    };
    map -> destroy();
    player -> destroy();
    map -> init(renderer, textureSize);
    gameObject -> setMap(map -> getMap());
    map -> draw();
    player -> setPosition(levelInfo -> strPosition, levelInfo -> colPosition);
    stepController -> setStep(levelInfo -> step, level);
    activeLevel = level;
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

