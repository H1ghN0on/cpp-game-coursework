#include "Player.h"
#include "Tile.h"
#include <iostream>
using namespace std;
void Player :: init () {
    stepController = new StepController;
    destObjectR.w = srcObjectR.w = 64;
    destObjectR.h = srcObjectR.h = 64;
    tilePosition = new TilePosition;
    move = new MoveInfo;
    srcObjectR.x = 0;
    srcObjectR.y = 0;
    objectTexture = IMG_LoadTexture(renderer, "assets/player.png");
    move -> direction = 0;
    move -> step = 2;
    move -> remain = 0;
}

void Player :: setPosition(int str, int col) {
    tilePosition -> str = str;
    tilePosition -> col = col;
    destObjectR.x = tile[str][col].getX();
    destObjectR.y = tile[str][col].getY();
    this -> setX(destObjectR.x);
    this -> setY(destObjectR.y);
}
void Player :: update() {
    switch (move -> direction) {
        case 0: {
            break;
        }
        case 1: {
            if (move -> remain) {
                this -> setY(y - move -> step);
                destObjectR.y = this -> getY();
                move -> remain--;
                return;
            }
            move -> direction = 0;
            break;
        }
        case 2: {
            if (move -> remain) {
                this -> setX(x + move -> step);
                destObjectR.x = this -> getX();
                move -> remain--;
                return;
            }
            move -> direction = 0;
            break;
        }
        case 3: {
            if (move -> remain) {
                this -> setY(y + move -> step);
                destObjectR.y = this -> getY();
                move -> remain--;
                return;
            }
            move -> direction = 0;
            break;
        }
        case 4: {
            if (move -> remain) {
                this -> setX(x - move -> step);
                destObjectR.x = this -> getX();
                move -> remain--;
                return;
            }
            move -> direction = 0;
            break;
        }
    }
}
void Player :: moveTo(int direction) {
    Tile firstNextTile;
    Tile secondNextTile;
    int firstNextLine;
    int secondNextLine;
    if (!move -> remain) {
        int str = tilePosition -> str;
        int col = tilePosition -> col;
        move -> remain = 64 / move -> step;
        switch (direction) {
            //top
            case 1: {
                firstNextLine = str - 1;
                secondNextLine = str - 2;
                if (firstNextLine >= 0) {
                    firstNextTile = tile[firstNextLine][col];
                }
                if (secondNextLine >= 0) {
                    secondNextTile = tile[secondNextLine][col];
                }
//                //player move
//                if (str - 1 >= 0 && firstNextTile.getType() != 1 && firstNextTile.getType() != 2) {
//                    move -> direction = 1;
//                    tilePosition -> str--;
//                } //box move;
//
//                else if (str - 2 >= 0 && firstNextTileType == 1 && secondNextTileType != 1 && secondNextTileType != 2 && firstNextTile.obstacle -> move -> direction == 0) {
//                    firstNextTile.obstacle -> moveTo(1);
//                    move -> direction = 0;
//                    move -> remain = 0;
//                } //monster move
//                else if (str - 2 >= 0 && firstNextTileType == 2 && secondNextTileType != 2 && secondNextTileType != 1 && firstNextTile.monster -> move -> direction == 0) {
//                    firstNextTile.monster -> moveTo(1);
//                    move -> direction = 0;
//                    move -> remain = 0;
//                } //monster destroy
//                else if (str - 2 >= 0 && firstNextTileType == 2 && secondNextTileType != 2 && (secondNextTileType == 1 || secondNextTileType == 2) && firstNextTile.monster -> move -> direction == 0) {
//                    move -> direction = 0;
//                    move -> remain = 0;
//                } else {
//                    move -> direction = 0;
//                    move -> remain = 0;
//                }
                this -> moveObject(firstNextTile, secondNextTile, firstNextLine, secondNextLine, direction);
                break;
            }
            // right
            case 2: {
                firstNextLine = col + 1;
                secondNextLine = col + 2;
                if (firstNextLine < 10) {
                    firstNextTile = tile[str][firstNextLine];
                }
                if (secondNextLine < 10) {
                    secondNextTile = tile[str][secondNextLine];
                }
//                if (col + 1 < 10 && tile[str][col + 1].getType() != 1 && tile[str][col + 1].getType() != 2) {
//                    move -> direction = 2;
//                    tilePosition -> col++;
//                } else if (col + 2 < 10 && tile[str][col + 1].getType() == 1 && tile[str][col + 2].getType() != 1 && tile[str][col + 2].getType() != 2 && tile[str][col + 1].obstacle -> move -> direction == 0) {
//                    tile[str][col + 1].obstacle -> moveTo(2);
//                    move -> direction = 0;
//                    move -> remain = 0;
//                } else if (col + 2 < 10 && tile[str][col + 1].getType() == 2 && tile[str][col + 2].getType() != 2 && tile[str][col + 2].getType() != 1 && tile[str][col + 1].monster -> move -> direction == 0) {
//                    tile[str][col + 1].monster -> moveTo(2);
//                    move -> direction = 0;
//                    move -> remain = 0;
//                } else if (col + 2 < 10 && tile[str][col + 1].getType() == 2 && tile[str][col + 2].getType() != 2 && tile[str][col + 1].monster -> move -> direction == 0) {
//                    move -> direction = 0;
//                    move -> remain = 0;
//                } else {
//                    move -> direction = 0;
//                    move -> remain = 0;
//                }
                this -> moveObject(firstNextTile, secondNextTile, firstNextLine, secondNextLine, direction);
                break;
            }
            //down
            case 3: {
                firstNextLine = str + 1;
                secondNextLine = str + 2;
                if (firstNextLine < 10) {
                    firstNextTile = tile[firstNextLine][col];
                }
                if (secondNextLine < 10) {
                    secondNextTile = tile[secondNextLine][col];
                }
//                if (firstNextLine >= 0) {
//                    firstNextTile = tile[firstNextLine][col];
//                    firstNextTileType = tile[firstNextLine][col].getType();
//                }
//                if (secondNextLine >= 0) {
//                    secondNextTile = tile[secondNextLine][col];
//                    secondNextTileType = tile[secondNextLine][col].getType();
//                }
//                if (str + 1 < 10 && tile[str + 1][col].getType() != 1 && tile[str + 1][col].getType() != 2) {
//                    move -> direction = 3;
//                    tilePosition -> str++;
//                } else if (str + 2 < 10 && tile[str + 1][col].getType() == 1 && tile[str + 2][col].getType() != 1 && tile[str + 2][col].getType() != 2 && tile[str + 1][col].obstacle -> move -> direction == 0) {
//                    tile[str + 1][col].obstacle -> moveTo(3);
//                    move -> direction = 0;
//                    move -> remain = 0;
//                } else if (str + 2 < 10 && tile[str + 1][col].getType() == 2 && tile[str + 2][col].getType() != 2 && tile[str + 2][col].getType() != 1 && tile[str + 1][col].monster -> move -> direction == 0) {
//                    tile[str + 1][col].monster -> moveTo(3);
//                    move -> direction = 0;
//                    move -> remain = 0;
//                } else if (str + 2 < 10 && tile[str + 1][col].getType() == 2 && tile[str + 2][col].getType() != 2 && tile[str + 1][col].monster -> move -> direction == 0) {
//                    move -> direction = 0;
//                    move -> remain = 0;
//                } else {
//                    move -> direction = 0;
//                    move -> remain = 0;
//                }
                this -> moveObject(firstNextTile, secondNextTile,firstNextLine, secondNextLine, direction);
                break;
            }
            //left
            case 4: {
                firstNextLine = col - 1;
                secondNextLine = col - 2;
                if (firstNextLine >= 0) {
                    firstNextTile = tile[str][firstNextLine];
                }
                if (secondNextLine >= 0) {
                    secondNextTile = tile[str][secondNextLine];
                }
//                if (col - 1 >= 0 && tile[str][col - 1].getType() != 1 && tile[str][col - 1].getType() != 2 ) {
//                    move -> direction = 4;
//                    tilePosition -> col--;
//                } else if (col - 2 >= 0 && tile[str][col - 1].getType() == 1 && tile[str][col - 2].getType() != 1 && tile[str][col - 2].getType() != 2 && tile[str][col - 1].obstacle -> move -> direction == 0) {
//                    tile[str][col - 1].obstacle -> moveTo(4);
//                    move -> direction = 0;
//                    move -> remain = 0;
//                } else if (col - 2 >= 0 && tile[str][col - 1].getType() == 2 && tile[str][col - 2].getType() != 2 && tile[str][col - 2].getType() != 1 && tile[str][col - 1].monster -> move -> direction == 0) {
//                    tile[str][col - 1].monster -> moveTo(4);
//                    move -> direction = 0;
//                    move -> remain = 0;
//                } else if (col - 2 >= 0 && tile[str][col - 1].getType() == 2 && tile[str][col - 2].getType() != 2 && tile[str][col - 1].monster -> move -> direction == 0) {
//                    move -> direction = 0;
//                    move -> remain = 0;
//                } else {
//                    move -> direction = 0;
//                    move -> remain = 0;
//                }
                this -> moveObject(firstNextTile, secondNextTile, firstNextLine, secondNextLine, direction);
                break;
            }
        }
    }
}

void Player :: moveObject(Tile firstNextTile, Tile secondNextTile, int firstNextLine, int secondNextLine, int direction) {
    //move to wall
    int str = tilePosition -> str;
    int col = tilePosition -> col;
    if (firstNextLine < 0 || firstNextLine >= 10) {
        move -> direction = 0;
        move -> remain = 0;
        return;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std :: vector <int> tileType = tile[i][j].getType();;
            int size = tileType.size();
            for (int k = 0; k < size; k++) {
                if (tileType[k] == 5) {
                    if (tile[i][j].trap -> getActive()) {
                        tile[i][j].trap -> setActive(false);
                    } else {
                        tile[i][j].trap -> setActive(true);
                    }
                }
            }
        }
    }
    if (firstNextTile.findType(5) && firstNextTile.trap -> getActive()) {
        stepController -> passStep();
    }
    stepController -> passStep();
    //trap active
    //player move
    if (firstNextLine >= 0 && firstNextLine < 10 && !firstNextTile.findType(1) && !firstNextTile.findType(2) &&  !firstNextTile.findType(3) && !firstNextTile.findType(4) ) {
        move -> direction = direction;
        switch (direction) {
            case 1: {
                tilePosition -> str--;
                break;
            }
            case 2: {
                tilePosition -> col++;
                break;
            }
            case 3: {
                tilePosition -> str++;
                break;
            }
            case 4: {
                tilePosition -> col--;
                break;
            }
        }
        cout << stepController -> getStep() << endl;
    } //box move;
    else if (secondNextLine >= 0 && secondNextLine < 10 && firstNextTile.findType(1)  && (!secondNextTile.findType(1) && !secondNextTile.findType(2) && !secondNextTile.findType(4)) && firstNextTile.obstacle -> move -> direction == 0) {
        firstNextTile.obstacle -> moveTo(direction);
        if (tile[str][col].findType(5) && tile[str][col].trap -> getActive()) {
            stepController -> passStep();
        }
        move -> direction = 0;
        move -> remain = 0;
        cout << stepController -> getStep() << endl;
    } //monster move
    else if (secondNextLine >= 0 && secondNextLine < 10 && firstNextTile.findType(2) && (!secondNextTile.findType(1) && !secondNextTile.findType(2) && !secondNextTile.findType(4)) && firstNextTile.monster -> move -> direction == 0) {
        firstNextTile.monster -> moveTo(direction);
        if (tile[str][col].findType(5) && !tile[str][col].trap -> getActive()) {
            stepController -> passStep();
        }
        move -> direction = 0;
        move -> remain = 0;
        cout << stepController -> getStep() << endl;
    } //monster destroy
    else if (secondNextLine >= 0 && secondNextLine < 10 && firstNextTile.findType(2) && (secondNextTile.findType(1) || secondNextTile.findType(2) || secondNextTile.findType(4)) && firstNextTile.monster -> move -> direction == 0) {
        firstNextTile.monster -> setDestroyFlag();
        if (tile[str][col].findType(5) && !tile[str][col].trap -> getActive()) {
            stepController -> passStep();
        }
        move -> direction = 0;
        move -> remain = 0;
        cout << stepController -> getStep() << endl;
    } else if ((secondNextLine == -1 || secondNextLine == 10) && firstNextTile.findType(2) && firstNextTile.monster -> move -> direction == 0){
        firstNextTile.monster -> setDestroyFlag();
        if (tile[str][col].findType(5) && !tile[str][col].trap -> getActive()) {
            stepController -> passStep();
        }
        move -> direction = 0;
        move -> remain = 0;
        cout << stepController -> getStep() << endl;
    }//key up
    else if (firstNextTile.findType(3)) {
        move -> direction = direction;
        switch (direction) {
            case 1: {
                tilePosition -> str--;
                break;
            }
            case 2: {
                tilePosition -> col++;
                break;
            }
            case 3: {
                tilePosition -> str++;
                break;
            }
            case 4: {
                tilePosition -> col--;
                break;
            }
        }
        keysId.push_back(firstNextTile.key -> getKeyId());
        firstNextTile.key -> setDestroyFlag();
        cout << stepController -> getStep() << endl;
    }//door
    else if (firstNextTile.findType(4)) {
        int size = keysId.size();
        int lockId = firstNextTile.lock -> getLockId();
        for (int i = 0; i < size; i++) {
            if (keysId[i] == lockId) {
                keysId.erase(keysId.begin() + i);
                firstNextTile.lock -> setDestroyFlag();
                move -> direction = direction;
                switch (direction) {
                    case 1: {
                        tilePosition -> str--;
                        break;
                    }
                    case 2: {
                        tilePosition -> col++;
                        break;
                    }
                    case 3: {
                        tilePosition -> str++;
                        break;
                    }
                    case 4: {
                        tilePosition -> col--;
                        break;
                    }
                }
                return;
            }
        }
        if (tile[str][col].findType(5) && !tile[str][col].trap -> getActive()) {
            stepController -> passStep();
        }
        move -> direction = 0;
        move -> remain = 0;
        cout << stepController -> getStep() << endl;
    } else {
        move -> direction = 0;
        move -> remain = 0;
        cout << stepController -> getStep() << endl;
    }
}

void Player :: destroy() {
    move -> direction = 0;
    move -> remain = 0;
    tilePosition -> str = 0;
    tilePosition -> col = 0;
    keysId.clear();
}
