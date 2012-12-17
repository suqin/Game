#include "player.h"

Player::Player()
{
    color=-1;
}
bool Player::IsMyTurn(int Color)
{
    qDebug()<<(Color==color);
    return (Color==color);
}
int Player::setcolor(int Color)
{
    color=Color;
    return color;
}

