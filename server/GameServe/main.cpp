#include <QCoreApplication>
#include "serverlistener.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ServerListener s;
    return a.exec();
}
