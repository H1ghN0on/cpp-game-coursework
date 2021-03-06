#include "Map.h"
#include "Tile.h"
#include "Box.h"
#include "Monster.h"
#include "Key.h"
#include <iostream>
#include "StepController.h"
#include "Trap.h"
#include "Level.h"
#include "LevelInfo.h"
using namespace std;

Tile** Map :: tile;

void Map :: init(SDL_Renderer* u_renderer, int textureSize_) {
    textureSize = textureSize_;
    destTileR.w = srcTileR.w = textureSize;
    destTileR.h = srcTileR.h = textureSize;
    srcTileR.x = srcTileR.y = 0;
    renderer = u_renderer;
    mapTile = IMG_LoadTexture(renderer, "assets/tile.png");
    box = IMG_LoadTexture(renderer, "assets/box.png");
    level_ = new Level;
    levelInfo_ = new LevelInfo;
    StepController *stepController = new StepController(levelInfo_ -> step, renderer);
    delete stepController;
    widthTileQuant = levelInfo_ -> widthTileQuant;
    heightTileQuant = levelInfo_ -> heightTileQuant;
    tile = new Tile*[widthTileQuant];
    for (int i = 0; i < widthTileQuant; i++) {
        tile[i] = new Tile[heightTileQuant];
    }
//    for (int i = 0; i < 10; i++) {
//        for (int j = 0; j < 10; j++) {
//            for (int k = 0; k < tile[i][j].type.size(); k++) {
//                cout << tile[i][j].type[k] << " ";
//            }
//            cout << endl;
//        }
//    }
}

void Map :: draw() {
    int dx = 0, dy = 0;
    int keyId = 0;
    int doorId = 0;
    for (int i = 0; i < widthTileQuant; i++) {
        for (int j = 0; j < heightTileQuant; j++) {
            tile[i][j].setType(0);
            for (int k = 1; k < level_ -> level[i][j][0] + 1; k++) {
                if (level_ -> level[i][j][k] != 0) {
                    tile[i][j].setType(level_ -> level[i][j][k]);
                }
            }
            tile[i][j].setX(dx);
            tile[i][j].setY(dy);
            std :: vector <int> tileType = tile[i][j].getType();
            int size = tileType.size();
            for (int k = 0; k < size; k++) {
                if (tileType[k] == 1) {
                    tile[i][j].obstacle = new Box;
                    tile[i][j].obstacle -> init(i, j);
                    boxes.push_back(tile[i][j].obstacle);
                }
                if (tileType[k] == 2) {
                    tile[i][j].monster = new Monster;
                    tile[i][j].monster -> init(i, j);
                    monsters.push_back(tile[i][j].monster);
                }
                if (tileType[k] == 3) {
                    tile[i][j].key = new Key;
                    tile[i][j].key -> init(i, j, keyId);
                    keys.push_back(tile[i][j].key);
                    keyId++;
                }
                if (tileType[k] == 4) {
                    tile[i][j].lock = new Lock;
                    tile[i][j].lock -> init(i, j, doorId);
                    locks.push_back(tile[i][j].lock);
                    doorId++;
                }
                if (tileType[k] == 5) {
                    tile[i][j].trap = new Trap;
                    tile[i][j].trap -> init(i, j, false);
                    traps.push_back(tile[i][j].trap);
                }
                if (tileType[k] == 6) {
                    tile[i][j].star = new Star;
                    tile[i][j].star -> init(i, j);
                    stars.push_back(tile[i][j].star);
                }
                if (tileType[k] == 7) {
                    tile[i][j].wall = new Wall;
                    tile[i][j].wall -> init(i, j);
                    walls.push_back(tile[i][j].wall);
                }
            }
            dx += textureSize;
        }
        dx = 0;
        dy += textureSize;
    }
}
void Map :: update() {
    int size = boxes.size();
    for (int i = 0; i < size; i++) {
        boxes[i] -> update();
        if (boxes[i] -> moveInfo -> remain == 1) {
            int str = boxes[i] -> tilePosition -> str;
            int col = boxes[i] -> tilePosition -> col;
            this -> obstacleSwitch(str, col, boxes[i] -> moveInfo -> direction, i);
        }
    }
    size = monsters.size();
    for (int i = 0; i < size; i++) {
        monsters[i] -> update();
        if (monsters[i] -> moveInfo -> remain == 1) {
            int str = monsters[i] -> tilePosition -> str;
            int col = monsters[i] -> tilePosition -> col;
            this -> monsterSwitch(str, col, monsters[i] -> moveInfo -> direction, i);
        }
        if (monsters[i] -> getDestroyFlag()) {
            int str = monsters[i] -> tilePosition -> str;
            int col = monsters[i] -> tilePosition -> col;
            tile[str][col].delType(2);
            delete tile[str][col].monster;
            tile[str][col].monster = NULL;
            monsters.erase(monsters.begin() + i);
        }
    }
    size = keys.size();
    for (int i = 0; i < size; i++) {
        if (keys[i] -> getDestroyFlag()) {
            int str = keys[i] -> tilePosition -> str;
            int col = keys[i] -> tilePosition -> col;
            tile[str][col].delType(3);
            delete tile[str][col].key;
            tile[str][col].key = NULL;
            keys.erase(keys.begin() + i);
        }
    }
    size = locks.size();
    for (int i = 0; i < size; i++) {
        if (locks[i] -> getDestroyFlag()) {
            int str = locks[i] -> tilePosition -> str;
            int col = locks[i] -> tilePosition -> col;
            tile[str][col].delType(4);
            delete tile[str][col].lock;
            tile[str][col].lock = NULL;
            locks.erase(locks.begin() + i);
        }
    }
}
void Map :: render() {
    for (int i = 0; i < widthTileQuant; i++) {
        for (int j = 0; j < heightTileQuant; j++) {
            destTileR.x = tile[i][j].getX();
            destTileR.y = tile[i][j].getY();
            SDL_RenderCopy(renderer, mapTile, &srcTileR, &destTileR);
        }
    }
    int size = traps.size();
    for (int i = 0; i < size; i++) {
        traps[i] -> render();
    }
    size = keys.size();
    for (int i = 0; i < size; i++) {
        keys[i] -> render();
    }
    size = boxes.size();
    for (int i = 0; i < size; i++) {
        boxes[i] -> render();
    }
    size = monsters.size();
    for (int i = 0; i < size; i++) {
        monsters[i] -> render();
    }
    size = locks.size();
    for (int i = 0; i < size; i++) {
        locks[i] -> render();
    }
    size = stars.size();
    for (int i = 0; i < size; i++) {
        stars[i] -> render();
    }
    size = walls.size();
    for (int i = 0; i < size; i++) {
        walls[i] -> render();
    }
}

Tile **Map :: getMap() {
    return tile;
}

void Map :: obstacleSwitch(int str, int col, int direction, int vectorPosition) {
    int strNew = str;
    int colNew = col;
    switch (direction) {
        case 1: {
            strNew--;
            break;
        }
        case 2: {
            colNew++;
            break;
        }
        case 3: {
            strNew++;
            break;
        }
        case 4: {
            colNew--;
            break;
        }
    }
    tile[strNew][colNew].setType(1);
    tile[strNew][colNew].obstacle = new Box;
    tile[strNew][colNew].obstacle -> init(strNew, colNew);
    tile[str][col].delType(1);
    delete tile[str][col].obstacle;
    tile[str][col].obstacle = NULL;
    boxes.erase(boxes.begin() + vectorPosition);
    boxes.push_back(tile[strNew][colNew].obstacle);
}

void Map :: monsterSwitch(int str, int col, int direction, int vectorPosition) {
    int strNew = str;
    int colNew = col;
    switch (direction) {
        case 1: {
            strNew--;
            break;
        }
        case 2: {
            colNew++;
            break;
        }
        case 3: {
            strNew++;
            break;
        }
        case 4: {
            colNew--;
            break;
        }
    }
    tile[strNew][colNew].setType(2);
    tile[strNew][colNew].monster = new Monster;
    tile[strNew][colNew].monster -> init(strNew, colNew);
    tile[str][col].delType(2);
    delete tile[str][col].monster;
    tile[str][col].monster = NULL;
    monsters.erase(monsters.begin() + vectorPosition);
    monsters.push_back(tile[strNew][colNew].monster);
}

void Map :: destroy() {
    for (int i = 0; i < widthTileQuant; i++) {
        for (int j = 0; j < heightTileQuant; j++) {
            tile[i][j].destroy();
        }
        delete[] tile[i];
    }
    delete[] tile;
    boxes.clear();
    monsters.clear();
    keys.clear();
    locks.clear();
    traps.clear();
    stars.clear();
    walls.clear();
    SDL_DestroyTexture(mapTile);
}
