#ifndef CORE_H
#define CORE_H
#define SIZE 15
#define COLOR_BLACK 10
#define COLOR_WHITE 1
#define WIN 2
#define CONTINUE 1
#define ERR 0
#include "../Public.h"
#include <QDebug>
class Core
{
public:
    Core();
    int play(int x,int y,int color);   //
    bool hasWin(int x, int y, int color);
    int getColor(int x,int y);
    void reset();
private:
    int chese[SIZE][SIZE];
    int num;                  //
};

#endif // CORE_H
