#include "Player.h"
#include "Tile.h"
#include <iostream>
using namespace std;
void Player :: init (StepController *stepController_, Profile* profile_) {
    profile = profile_;
    stepController = stepController_;
    objectTexture = IMG_LoadTexture(renderer, "assets/static_new.png");
    destObjectR.w = srcObjectR.w = textureSize;
    destObjectR.h = srcObjectR.h = textureSize;
    srcObjectR.x = 0;
    srcObjectR.y = 0;
    moveInfo -> direction = 0;
    moveInfo -> step = 1;
    moveInfo -> remain = 0;
}

void Player :: setPosition(int str, int col) {
    tilePosition -> str = str;
    tilePosition -> col = col;
    destObjectR.x = tile[str][col].getX();
    destObjectR.y = tile[str][col].getY();
    x = destObjectR.x;
    y = destObjectR.y;
}

void Player :: changeDirection(int direction) {
     switch (direction) {
        case 1: {
            srcObjectR.y = 64;
            srcObjectR.x = 0;
            break;
        }
        case 2: {
            srcObjectR.y = 128;
            srcObjectR.x = 0;
            break;
        }
        case 3: {
            srcObjectR.y = 0;
            srcObjectR.x = 0;
            break;
        }
        case 4: {
            srcObjectR.y = 192;
            srcObjectR.x = 0;
            break;
        }
    }
}
void Player :: update() {
    switch (moveInfo -> direction) {
        case 0: {
            break;
        }
        case 1: {
//            if (moveInfo -> remain) {
//                this -> move();
//                this -> setY(y - moveInfo -> step);
//                destObjectR.y = this -> getY();
//                moveInfo -> remain--;
//                return;
//            }
//            counter = 0;
            moveInfo -> remain = 0;
            y -= 64;
            destObjectR.y = y;
            this -> changeDirection(moveInfo -> direction);
            moveInfo -> direction = 0;
            break;
        }
        case 2: {
//            if (moveInfo -> remain) {
//                this -> move();
//                this -> setX(x + moveInfo -> step);
//                destObjectR.x = this -> getX();
//                moveInfo -> remain--;
//                return;
//            }
//            counter = 0;
            moveInfo -> remain = 0;
            x += 64;
            destObjectR.x = x;
            this -> changeDirection(moveInfo -> direction);
            moveInfo -> direction = 0;
            break;
        }
        case 3: {
//            if (moveInfo -> remain) {
//                this -> move();
//                this -> setY(y + moveInfo -> step);
//                destObjectR.y = this -> getY();
//                moveInfo -> remain--;
//                return;
//            }
//            counter = 0;
            moveInfo -> remain = 0;
            y += 64;
            destObjectR.y = y;
            this -> changeDirection(moveInfo -> direction);
            moveInfo -> direction = 0;
            break;
        }
        case 4: {
//            if (moveInfo -> remain) {
//                this -> move();
//                this -> setX(x - moveInfo -> step);
//                destObjectR.x = this -> getX();
//                moveInfo -> remain--;
//                return;
//            }
//            counter = 0;
            moveInfo -> remain = 0;
            x -= 64;
            destObjectR.x = x;
            this -> changeDirection(moveInfo -> direction);
            moveInfo -> direction = 0;
            break;
        }
    }
}

void Player :: render() {
    destObjectR.x = getX();
    destObjectR.y = getY();
    SDL_RenderCopy(renderer, objectTexture, &srcObjectR, &destObjectR);
}

void Player :: moveTo(int direction) {
    Tile firstNextTile;
    Tile secondNextTile;
    int firstNextLine;
    int secondNextLine;
    if (!moveInfo -> remain) {
        int str = tilePosition -> str;
        int col = tilePosition -> col;
        moveInfo -> remain = textureSize / moveInfo -> step;
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
                this -> moveObject(firstNextTile, secondNextTile, firstNextLine, secondNextLine, direction);
                break;
            }
            // right
            case 2: {
                firstNextLine = col + 1;
                secondNextLine = col + 2;
                if (firstNextLine < 12) {
                    firstNextTile = tile[str][firstNextLine];
                }
                if (secondNextLine < 12) {
                    secondNextTile = tile[str][secondNextLine];
                }
                this -> moveObject(firstNextTile, secondNextTile, firstNextLine, secondNextLine, direction);
                break;
            }
            //down
            case 3: {
                firstNextLine = str + 1;
                secondNextLine = str + 2;
                if (firstNextLine < 12) {
                    firstNextTile = tile[firstNextLine][col];
                }
                if (secondNextLine < 12) {
                    secondNextTile = tile[secondNextLine][col];
                }
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
                this -> moveObject(firstNextTile, secondNextTile, firstNextLine, secondNextLine, direction);
                break;
            }
        }
    }
}

void Player :: moveObject(Tile firstNextTile, Tile secondNextTile, int firstNextLine, int secondNextLine, int direction) {
    this -> changeDirection(direction);
    auto toDir {
        [this](int direction) {
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
        }
    };
    //move to wall
    int str = tilePosition -> str;
    int col = tilePosition -> col;
    if (firstNextTile.findType(6)) {
        stepController -> setStep(-10, renderer);
        isLevelPassed = true;
        if (profile -> getLastPassedLevel() == stepController -> level && stepController -> level != 5) {
            profile -> setLastPassedLevel();
            profile -> saveFile();
        }
    }
    if (firstNextLine < 0 || firstNextLine >= 12 || firstNextTile.findType(7)) {
        moveInfo -> direction = 0;
        moveInfo -> remain = 0;
        return;
    }
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            std :: vector <int> tileType = tile[i][j].getType();;
            int size = tileType.size();
            for (int k = 0; k < size; k++) {
                if (tileType[k] == 1) {
                    if (tile[i][j].obstacle -> moveInfo -> direction != 0) {
                        break;
                    }
                }
                if (tileType[k] == 2) {
                    if (tile[i][j].monster -> moveInfo -> direction != 0) {
                        break;
                    }
                }
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
    if (firstNextTile.findType(5) && firstNextTile.trap -> getActive() && !firstNextTile.findType(1) && !firstNextTile.findType(2) && !firstNextTile.findType(4)) {
        stepController -> passStep();
    }
    stepController -> passStep();
    //trap active
    //player move
    if (firstNextLine >= 0 && firstNextLine < 12 && !firstNextTile.findType(1) && !firstNextTile.findType(2) &&  !firstNextTile.findType(3) && !firstNextTile.findType(4) ) {
        moveInfo -> direction = direction;
        this -> changeDirection(direction);
        toDir(direction);
    } //box move;
    else if (secondNextLine >= 0 && secondNextLine < 12 && !secondNextTile.findType(7) && firstNextTile.findType(1)  && (!secondNextTile.findType(1) && !secondNextTile.findType(6) &&  !secondNextTile.findType(2) && !secondNextTile.findType(4)) && firstNextTile.obstacle -> moveInfo -> direction == 0) {
        firstNextTile.obstacle -> moveTo(direction);
        if (tile[str][col].findType(5) && tile[str][col].trap -> getActive()) {
            stepController -> passStep();
        }
        moveInfo -> direction = 0;
        moveInfo -> remain = 0;
    } //monster move
    else if (secondNextLine >= 0 && secondNextLine < 12 && firstNextTile.findType(2) && (!secondNextTile.findType(1) && !secondNextTile.findType(2) && !secondNextTile.findType(6) && !secondNextTile.findType(4) && !secondNextTile.findType(7)) && firstNextTile.monster -> moveInfo -> direction == 0) {
        firstNextTile.monster -> moveTo(direction);
        if (tile[str][col].findType(5) && tile[str][col].trap -> getActive()) {
            stepController -> passStep();
        }
        moveInfo -> direction = 0;
        moveInfo -> remain = 0;
    } //monster destroy
    else if (secondNextLine >= 0 && secondNextLine < 12 && firstNextTile.findType(2) && (secondNextTile.findType(1) || secondNextTile.findType(7) || secondNextTile.findType(6) || secondNextTile.findType(2) || secondNextTile.findType(4)) && firstNextTile.monster -> moveInfo -> direction == 0) {
        firstNextTile.monster -> setDestroyFlag();
        if (tile[str][col].findType(5) && tile[str][col].trap -> getActive()) {
            stepController -> passStep();
        }
        moveInfo -> direction = 0;
        moveInfo -> remain = 0;
    } else if ((secondNextLine == -1 || secondNextLine == 12 || firstNextTile.findType(7)) && firstNextTile.findType(2) && firstNextTile.monster -> moveInfo -> direction == 0){
        firstNextTile.monster -> setDestroyFlag();
        if (tile[str][col].findType(5) && tile[str][col].trap -> getActive()) {
            stepController -> passStep();
        }
        moveInfo -> direction = 0;
        moveInfo -> remain = 0;
    }//key up
    else if (firstNextTile.findType(3) && !firstNextTile.findType(1) && !firstNextTile.findType(2)) {
        moveInfo -> direction = direction;
        this -> changeDirection(direction);
        toDir(direction);
        keysId.push_back(firstNextTile.key -> getKeyId());
        firstNextTile.key -> setDestroyFlag();
    }//door
    else if (firstNextTile.findType(4)) {
        int size = keysId.size();
        int lockId = firstNextTile.lock -> getLockId();
        for (int i = 0; i < size; i++) {
            if (keysId[i] == lockId) {
                keysId.erase(keysId.begin() + i);
                firstNextTile.lock -> setDestroyFlag();
                moveInfo -> direction = direction;
                this -> changeDirection(direction);
                toDir(direction);
                return;
            }
        }
        if (tile[str][col].findType(5) && tile[str][col].trap -> getActive()) {
            stepController -> passStep();
        }
        moveInfo -> direction = 0;
        moveInfo -> remain = 0;
    } else {
        moveInfo -> direction = 0;
        moveInfo -> remain = 0;
    }
}

bool Player :: getIsLevelPassed() {
    return isLevelPassed;
}

void Player :: setIsLevelPassed(bool status) {
    isLevelPassed = status;
}

void Player :: destroy() {
    moveInfo -> direction = 0;
    moveInfo -> remain = 0;
    tilePosition -> str = 0;
    tilePosition -> col = 0;
    this -> changeDirection(3);
    keysId.clear();
}
