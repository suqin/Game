#include "userlist.h"

UserList::UserList()
{

    for(int i=0;i<MAXCONNECTION;i++)
        users[i]=NULL;
    current=0;
}
int UserList::Insert(User *user)
{
    for(int i=0;i<MAXCONNECTION;i++)
    {
        if(users[i]==NULL)
        {
            users[i]=user;
            qDebug()<<__FUNCTION__<<user->name;
            return 1;
        }
    }
    return -1;
}

struct User * UserList::GetUser(int i)
{
    return users[i];
}

struct User * UserList::Next()
{

    for(;;)
    {
        current++;
        if(users[current-1]!=NULL)
            return users[current-1];
        if(current==MAXCONNECTION)
        {
            current=0;
            return NULL;
        }
    }
}

void UserList::Del(int i)
{
    if(users[i]!=NULL)
    {
        delete users[i];
        users[i]=NULL;
    }
}
int UserList::Del(QTcpSocket *socket)
{
    for(int i=0;i<MAXCONNECTION;i++)
    {
        if(users[i]!=NULL
           &&users[i]->port==socket->peerPort()
           &&users[i]->add==socket->peerAddress())
        {
            qDebug()<<users[i]->name<<users[i]->port;
            delete users[i];
            qDebug()<<__FUNCTION__<<"ok";
            users[i]=NULL;
            return i;
        }
    }
    return 0;
}

UserList::~UserList()
{
    for(int i=0;i<MAXCONNECTION;i++)
    {
        if(users[i]!=NULL)
            delete users[i];
    }
}

struct User * UserList::FindBySocket(QTcpSocket *socket)
{
    for(int i=0;i<MAXCONNECTION;i++)
    {
        if(users[i]!=NULL
           &&users[i]->port==socket->peerPort()
           &&users[i]->add==socket->peerAddress())
        {
            qDebug()<<users[i]->name<<users[i]->port;
            return users[i];
        }
    }
    return NULL;
}

struct User * UserList::FindByName(QString name)
{
    for(int i=0;i<MAXCONNECTION;i++)
    {
        if(users[i]->name==name)
        {
            qDebug()<<__FUNCTION__<<"find!";
            return users[i];
        }
    }
    return NULL;
}








