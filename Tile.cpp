#include "Tile.h"
#include <iostream>
using namespace std;
std :: vector<int> Tile :: getType() {
    return type;
}

void Tile :: setType(const int& u_type) {
    type.push_back(u_type);
}

void Tile :: delType(const int& u_type) {
    int size = type.size();
    for (int i = 0; i < size; i++) {
        if (type[i] == u_type) {
            type.erase(type.begin() + i);
            return;
        }
    }
}

void Tile :: destroy() {
    int size = type.size();
    for (int i = 0; i < size; i++) {
        switch (type[i]) {
            case 1: {
                delete this -> obstacle;
                break;
            }
            case 2: {
                delete this -> monster;
                break;
            }
            case 3: {
                delete this -> key;
                break;
            }
            case 4: {
                delete this -> lock;
                break;
            }
            case 5: {
                delete this -> trap;
                break;
            }
            case 6: {
                delete this -> star;
                break;
            }
            case 7: {
                delete this -> wall;
                break;
            }

        }
    }
    type.clear();
}

bool Tile :: findType(const int& u_type) {
    int size = type.size();
    for (int i = 0; i < size; i++) {
        if (type[i] == u_type) {
            return true;
        }
    }
    return false;
}
