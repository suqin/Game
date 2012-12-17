#include <QCoreApplication>
#include "db.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DB db;
    return a.exec();
}
