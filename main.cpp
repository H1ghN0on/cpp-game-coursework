#include "Game.h"
#include <string>
#include <iostream>

using namespace std;

int width = 768;
int height = 832;
const int FPS = 220;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;
int main(int argc, char** argv) {

    const char* title = "Shinzo wo Sasageyo!";

    //�������� ��������� ����
    Game& game = Game :: instance();

    game.init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    while (game.running()) {

        frameStart = SDL_GetTicks();

        //��������� �������, ���������� ��������� � ��������� �������� � ����������� �����
        game.handleEvents();
        game.update();
        game.render();

        //�������� ���
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game.clean();
    return 0;
}
