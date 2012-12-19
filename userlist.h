#ifndef USERLIST_H
#define USERLIST_H

#include <QObject>
#include <QtNetwork>
#include "Public.h"
struct User
{
    QString name;
    QHostAddress add;
    quint16 port;
    bool online;

};

class UserList
{
public:
    UserList();
    ~UserList();
    int Insert(User *user);
    struct User *GetUser(int i);
    struct User *Next();
    struct User *FindByName(QString name);
    struct User *FindBySocket(QTcpSocket *soc);
    void Del(int i);
    int Del(QTcpSocket *socket);
private:
    struct User *users[MAXCONNECTION];
    int current;
    
};

#endif // USERLIST_H
