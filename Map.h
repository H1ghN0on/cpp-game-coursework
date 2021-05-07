#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>
class Trap;
class Box;
class Monster;
class Tile;
class Key;
class Lock;
class Map {
private:
    SDL_Texture *box = NULL;
    SDL_Texture *mapTile = NULL;
    SDL_Renderer *renderer = NULL;
    Tile **tile = NULL;
    SDL_Rect srcTileR;
    SDL_Rect destTileR;
    int widthTileQuant;
    int heightTileQuant;
    class Level {
    public:
        const int widthTileQuant = 10;
        const int heightTileQuant = 10;
        int level[10][10] = {
           {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
           {0, 0, 0, 0, 0, 1, 0, 0, 4, 0},
           {0, 0, 1, 0, 2, 0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
           {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
           {0, 0, 1, 5, 5, 5, 5, 1, 0, 0},
           {0, 0, 0, 0, 1, 0, 0, 3, 0, 0},
           {0, 2, 0, 0, 2, 0, 1, 0, 0, 0},
           {0, 0, 1, 0, 0, 0, 0, 0, 0, 3},
        };
        int step = 20;
    };
    std :: vector <Box*> boxes;
    std :: vector <Monster*> monsters;
    std :: vector <Key*> keys;
    std :: vector <Lock*> locks;
    std :: vector <Trap*> traps;
//    std :: vector <Monster*> monsters;
    void obstacleSwitch(int str, int col, int direction, int vectorPosition);
    void monsterSwitch(int str, int col, int direction, int vectorPosition);
    Level *level_ = NULL;

public:
    void init(SDL_Renderer *u_renderer);
    void update();
    void render();
    void draw();
    Tile **getMap();
};

#endif // MAP_H_INCLUDED
