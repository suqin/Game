#include "net.h"

Net::Net(QObject *parent) :
    QObject(parent)
{
    serverSocket = new QTcpServer();
    serverSocket->listen(QHostAddress::LocalHost,DBSERVERPORT)
}
