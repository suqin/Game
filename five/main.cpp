
#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(0,argv[1],argv[2],argv[3],argv[4]);
    w.show();
    
    return a.exec();
}
