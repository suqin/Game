#ifndef SERVERLISTENER_H
#define SERVERLISTENER_H

#include <QObject>
#include <QtNetwork>
#include <QAbstractSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include "../../Public.h"
#include "../../userlist.h"
#include "../../packagereader.h"
class ServerListener : public QObject
{
    Q_OBJECT
public:
    explicit ServerListener(QObject *parent = 0);
    
signals:
    void hasNewData(QAbstractSocket *,UserList *);//发送信号给PackageReader进行解析
    
public slots:
    void hasNewConn();//有新的连接
    void hasData();   //有数据可读
    void onSocketError(QAbstractSocket::SocketError s);//错误处理
    void GetSocketByName(QAbstractSocket *socket,QString name);
private:
    QTcpServer *MainServer;                            //主套结字
    QTcpSocket *clients[MAXCONNECTION];                //客户端队列
    PackageReader *reader;                             //数据包解析类
    UserList *list;
};

#endif // SERVERLISTENER_H
