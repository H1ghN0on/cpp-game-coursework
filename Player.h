#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <vector>
#include "DynamicGameObject.h"
#include "StepController.h"
class Tile;
class Key;
class StepController;
class Player : public DynamicGameObject {
protected:
    StepController *stepController;
    MoveInfo *move;
    std :: vector <int> keysId;
public:
    void init();
    void update();
    void moveTo(int direction);
    void moveObject(Tile firstNextTile, Tile secondNextTile, int firstNextLine, int secondNextLine, int direction);
};

#endif // PLAYER_H_INCLUDED
