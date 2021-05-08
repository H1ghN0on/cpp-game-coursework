#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>
class Level;
class LevelInfo;
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
    static Tile **tile;
    SDL_Rect srcTileR;
    SDL_Rect destTileR;
    int widthTileQuant;
    int heightTileQuant;
    std :: vector <Box*> boxes;
    std :: vector <Monster*> monsters;
    std :: vector <Key*> keys;
    std :: vector <Lock*> locks;
    std :: vector <Trap*> traps;
    void obstacleSwitch(int str, int col, int direction, int vectorPosition);
    void monsterSwitch(int str, int col, int direction, int vectorPosition);
    Level *level_ = NULL;
    LevelInfo *levelInfo_ = NULL;

public:
    void init(SDL_Renderer *u_renderer);
    void update();
    void render();
    void draw();
    void destroy();
    Tile **getMap();
};

#endif // MAP_H_INCLUDED
