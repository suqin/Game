#include "core.h"

Core::Core()
{
    memset(chese,0,SIZE*SIZE*sizeof(int));
    num=0;
}
int Core::getColor(int x, int y)
{
    return chese[x][y];
}
void Core::reset()
{
    memset(chese,0,SIZE*SIZE*sizeof(int));
    num=0;
}

int Core::play(int x, int y, int color)
{
    if(chese[x][y])
        return ERR;
    chese[x][y]=color;
    num++;
    if(hasWin(x,y,color)) {

        qDebug()<<"win";
        return WIN;
    }
    return CONTINUE;
}

bool Core::hasWin(int x,int y,int color)
{
    int x_temp,y_temp,i,sum;
    for(x_temp=x, y_temp=y-4;y_temp<=y ; y_temp++) {
        for(sum=0,i=0; i<5;i++ ) {
            if(y_temp+i < 0 || y_temp+i >= SIZE)
                break;
            sum+=chese[x_temp][y_temp+i];
        }
        if(sum == color*5)
            return 1;
    }
    for(x_temp=x-4, y_temp=y;x_temp<=x ;x_temp++ ) {
        for(sum=0,i=0;i<5 ; i++) {
            if(x_temp+i < 0 || x_temp+i >= SIZE)
                break;
            sum+=chese[x_temp+i][y_temp];
        }
        if(sum == color*5)
            return 1;
    }
    for(x_temp=x-4, y_temp=y-4;x_temp<=x ;x_temp++,y_temp++ ) {
        for(sum=0,i=0;i<5 ; i++) {
            if(x_temp+i < 0 || x_temp+i >= SIZE || y_temp+i < 0 || y_temp+i >= SIZE)
                break;
            sum+=chese[x_temp+i][y_temp+i];
        }
        if(sum == color*5)
            return 1;
    }
    for(x_temp=x-4, y_temp=y+4;x_temp<=x ;x_temp++,y_temp-- ) {
        for(sum=0,i=0;i<5 ; i++) {
            if(x_temp+i < 0 || x_temp+i >= SIZE || y_temp-i < 0 || y_temp-i >= SIZE)
                break;
            sum+=chese[x_temp+i][y_temp-i];
        }
        if(sum == color*5)
            return 1;
    }

    return 0;
}
