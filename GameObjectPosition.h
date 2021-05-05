#ifndef GAMEOBJECTPOSITION_H_INCLUDED
#define GAMEOBJECTPOSITION_H_INCLUDED

class GameObjectPosition {
protected:
    int x, y;
public:
    int getX();
    int getY();
    void setX(int u_x);
    void setY(int u_y);
};

#endif // GAMEOBJECTPOSITION_H_INCLUDED
