#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <vector>
#include "DynamicGameObject.h"
#include "StepController.h"
#include "PlayerAnimation.h"
#include "Profile.h"
class Tile;
class Profile;
class Key;
class StepController;
class PlayerAnimation;
class Player : public DynamicGameObject, public PlayerAnimation {
protected:
    Profile *profile = NULL;
    StepController *stepController = NULL;
    MoveInfo *moveInfo;
    std :: vector <int> keysId;
    bool isLevelPassed = false;
public:
    void init(StepController* stepController_, Profile *profile);
    void setPosition(int str, int col);
    void update();
    void render();
    void moveTo(int direction);
    void moveObject(Tile firstNextTile, Tile secondNextTile, int firstNextLine, int secondNextLine, int direction);
    void destroy();
    bool getIsLevelPassed();
    void setIsLevelPassed(bool status);
};

#endif // PLAYER_H_INCLUDED
