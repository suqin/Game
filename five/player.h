#ifndef PLAYER_H
#define PLAYER_H
#include <QString>
#include "../Public.h"
#include <QDebug>
class Player
{
public:
    Player();
    int getColor() {return color;}
    bool IsMyTurn(int Color);
    int setcolor(int Color);
private:
    int color;
};

#endif // PLAYER_H
