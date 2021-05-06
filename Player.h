#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <vector>
#include "DynamicGameObject.h"
class Tile;
class Key;
class Player : public DynamicGameObject {
protected:
    MoveInfo *move;
    std :: vector <int> keysId;
public:
    void init();
    void update();
    void moveTo(int direction);
    void moveObject(Tile firstNextTile, Tile secondNextTile, std :: vector <int> firstNextTileType, std :: vector <int> secondNextTileType, int firstNextLine, int secondNextLine, int direction);
};

#endif // PLAYER_H_INCLUDED
