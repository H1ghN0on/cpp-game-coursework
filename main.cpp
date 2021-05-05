#include "Game.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    const char* title = "Shinzo wo Sasageyo!";
	if (!SDL_Init(SDL_INIT_EVERYTHING)) {
		Game& game = Game :: instance();
		game.init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, 0);
		while (game.running()) {
            game.handleEvents();
            game.update();
            game.render();
        }
        game.clean();
	}
	cout << endl;
    return 0;
}
