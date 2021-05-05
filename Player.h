#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "GameObject.h"
class Tile;
class Player : public GameObject {
protected:
    TilePosition *tilePosition;
    MoveInfo *move;
public:
    void init();
    void update();
    void moveTo(int direction);
    void render();
    void moveObject(Tile firstNextTile, Tile secondNextTile, int firstNextTileType, int secondNextTileType, int firstNextLine, int secondNextLine, int direction);
};

#endif // PLAYER_H_INCLUDED
