#include "Map.h"
#include "Tile.h"
#include "Box.h"
#include "Monster.h"
#include "Key.h"
#include <iostream>
using namespace std;

void Map :: init(SDL_Renderer* u_renderer) {
    destTileR.w = srcTileR.w = 64;
    destTileR.h = srcTileR.h = 64;
    srcTileR.x = srcTileR.y = 0;
    renderer = u_renderer;
    mapTile = IMG_LoadTexture(renderer, "assets/tile.png");
    box = IMG_LoadTexture(renderer, "assets/box.png");
    int dx = 0, dy = 0;
    Level *level_ = new Level;
    widthTileQuant = level_ -> widthTileQuant;
    heightTileQuant = level_ -> heightTileQuant;
    tile = new Tile*[widthTileQuant];
    for (int i = 0; i < widthTileQuant; i++) {
        tile[i] = new Tile[heightTileQuant];
         for (int j = 0; j < heightTileQuant; j++) {
            tile[i][j].setType(level_ -> level[i][j]);
            tile[i][j].setX(dx);
            tile[i][j].setY(dy);
            dx += 64;
        }
        dx = 0;
        dy += 64;
    }
    dx = 0;
    dy += 64;
}

void Map :: draw() {
    int keyId = 0;
    int doorId = 0;
    for (int i = 0; i < widthTileQuant; i++) {
        for (int j = 0; j < heightTileQuant; j++) {
            if (tile[i][j].getType() == 1) {
                tile[i][j].obstacle = new Box;
                tile[i][j].obstacle -> init(i, j);
                boxes.push_back(tile[i][j].obstacle);
            }
            if (tile[i][j].getType() == 2) {
                tile[i][j].monster = new Monster;
                tile[i][j].monster -> init(i, j);
                monsters.push_back(tile[i][j].monster);
            }
            if (tile[i][j].getType() == 3) {
                tile[i][j].key = new Key;
                tile[i][j].key -> init(i, j, keyId);
                keys.push_back(tile[i][j].key);
                keyId++;
            }
            if (tile[i][j].getType() == 4) {
                tile[i][j].lock = new Lock;
                tile[i][j].lock -> init(i, j, doorId);
                locks.push_back(tile[i][j].lock);
                doorId++;
            }
        }
    }
}
void Map :: update() {
    int size = boxes.size();
    for (int i = 0; i < size; i++) {
        boxes[i] -> update();
        if (boxes[i] -> move -> remain == 1) {
            int str = boxes[i] -> tilePosition -> str;
            int col = boxes[i] -> tilePosition -> col;
            this -> obstacleSwitch(str, col, boxes[i] -> move -> direction, i);
        }
    }
    size = monsters.size();
    for (int i = 0; i < size; i++) {
        monsters[i] -> update();
        if (monsters[i] -> move -> remain == 1) {
            int str = monsters[i] -> tilePosition -> str;
            int col = monsters[i] -> tilePosition -> col;
            this -> monsterSwitch(str, col, monsters[i] -> move -> direction, i);
        }
        if (monsters[i] -> getDestroyFlag()) {
            int str = monsters[i] -> tilePosition -> str;
            int col = monsters[i] -> tilePosition -> col;
            tile[str][col].setType(0);
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
            tile[str][col].setType(0);
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
            tile[str][col].setType(0);
            delete tile[str][col].key;
            tile[str][col].key = NULL;
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
    int size = keys.size();
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
    if (tile[str][col].key == NULL) {
        tile[str][col].setType(0);
    } else {
        tile[str][col].setType(3);
    }
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
    if (tile[str][col].key == NULL) {
        tile[str][col].setType(0);
    } else {
        tile[str][col].setType(3);
    }
    delete tile[str][col].monster;
    tile[str][col].monster = NULL;
    monsters.erase(monsters.begin() + vectorPosition);
    monsters.push_back(tile[strNew][colNew].monster);
}
