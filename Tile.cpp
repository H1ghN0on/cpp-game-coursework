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

bool Tile :: findType(const int& u_type) {
    int size = type.size();
    for (int i = 0; i < size; i++) {
        if (type[i] == u_type) {
            return true;
        }
    }
    return false;
}
