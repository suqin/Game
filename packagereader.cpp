#include "packagereader.h"

PackageReader::PackageReader(QObject *parent, QTcpSocket **_clients) :
    QObject(parent)
{
    clients = _clients;
    db = new Db();
    //sock=NULL;

}
void PackageReader::ReadData(QAbstractSocket *socket, UserList *list)
{
    QDataStream socketStream;
    socketStream.setVersion(QDataStream::Qt_4_8);
    socketStream.setDevice(socket);
    l=list;
    s=socket;
    int cmd;
    socketStream>>cmd;
    QString data1,data2;
    qDebug()<<cmd;
    switch (cmd)
    {
    case CMD_LOGIN:
        if(Login())
        {
            SendLists();

        }
        else
            qDebug()<<"login fault";
        break;
    case CMD_GET_LIST:
        qDebug()<<SendLists();

        break;
    case CMD_REG:
        Reg();
        break;
    case CMD_GAME_REQ:
        GameReq();
        break;
    default:
        break;
    }
}
void PackageReader::GameReq()
{
    QTcpSocket *socket=NULL;
    QDataStream socketStream;
    socketStream.setVersion(QDataStream::Qt_4_8);
    socketStream.setDevice(s);
    int nameLen;
    QString name;
    socketStream>>nameLen;
    name.resize(nameLen);
    socketStream>>name;

    struct User *user;
    user=l->FindByName(name);
    for(int i=0;i<MAXCONNECTION;i++)
    {
        if(clients[i]->peerAddress()==user->add &&
           clients[i]->peerPort()==user->port)
        {
            socket=clients[i];
            qDebug()<<__FUNCDNAME__<<"find it!";
            break;
        }
    }
    if(socket!=NULL)
    {
            qDebug()<<__FUNCTION__<<name;
            QDataStream socketStreamToClient;
            socketStream.setVersion(QDataStream::Qt_4_8);
            socketStreamToClient.setDevice(socket);
            socketStreamToClient<<CMD_GAME_REQ

                                <<s->peerAddress().toString()
                                <<s->peerPort()
                                <<name.size()
                               <<name;

    }
}

bool PackageReader::Login()
{

    QDataStream socketStream;
    socketStream.setVersion(QDataStream::Qt_4_8);
    socketStream.setDevice(s);
    struct User *user;
    int nameLen,passwdLen;
    QString name,passwd;
    socketStream>>nameLen;
    if(nameLen<0||nameLen>MAX_STR_LEN)
    {
        socketStream<<FAULT;
        return 0;
    }
    name.resize(nameLen);
    socketStream>>name;
    socketStream>>passwdLen;
    if(passwdLen<0||passwdLen>MAX_STR_LEN)
    {
        socketStream<<FAULT;
        return 0;
    }
    passwd.resize(passwdLen);
    socketStream>>passwd;
    qDebug()<<"user name"<<name<<"passwd:"<<passwd;
    if(!db->IsMatch(name,passwd))
    {

        socketStream<<FAULT;
    }
    user = new struct User;
    user->name=name;
    user->add=s->peerAddress();
    user->online=1;
    user->port=s->peerPort();

    qDebug()<<user->name;
    if(-1==l->Insert(user))
    {
        delete user;
        socketStream<<FAULT;
        return 0;
    }

    socketStream<<SUCCEED;
    emit LogSucceed(user);
    return 1;

}
int PackageReader::SendLists()
{
    QDataStream socketStream;
    socketStream.setVersion(QDataStream::Qt_4_8);
    socketStream.setDevice(s);
    qDebug()<<__FUNCTION__;
    int count=0;
    struct User *user;

    QByteArray data;
    for(;;)
    {

        QDataStream stream(&data,QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_4_8);
        user=l->Next();
        if(user==NULL)
        {
            qDebug()<<__FUNCTION__<<"end";
            return count;

        }
        qDebug()<<user->name;
        stream<<VAL_USER
              <<user->name.length()
              <<user->name
              <<user->add.toIPv4Address()
              <<user->port
              <<user->online;
        socketStream.writeRawData(data.data(),data.size());
        count++;
        qDebug()<<__FUNCTION__<<"count"<<count;
   }
}

void PackageReader::DeleteUser(QAbstractSocket *socket,QString &user)
{
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_4_8);
    QDataStream socketStream;
    socketStream.setVersion(QDataStream::Qt_4_8);
    socketStream.setDevice(socket);
    qDebug()<<__FUNCTION__;
    stream<<CMD_DEL_USER
          <<user.size()
          <<user;
    socketStream.writeRawData(data.data(),data.size());
}

void PackageReader::SendUser(QAbstractSocket *socket, User *user)
{
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_4_8);
    QDataStream socketStream;
    socketStream.setVersion(QDataStream::Qt_4_8);
    socketStream.setDevice(socket);
    qDebug()<<__FUNCTION__;
    stream<<VAL_USER
          <<user->name.length()
          <<user->name
          <<user->add.toIPv4Address()
          <<user->port
          <<user->online;
    socketStream.writeRawData(data.data(),data.size());
}
bool PackageReader::Reg()
{
    QDataStream socketStream;
    socketStream.setVersion(QDataStream::Qt_4_8);
    socketStream.setDevice(s);
    int nameLen,passwdLen;
    QString name,passwd;
    socketStream>>nameLen;
    if(nameLen<0||nameLen>MAX_STR_LEN)
    {
        socketStream<<FAULT;
        return 0;
    }
    name.resize(nameLen);
    socketStream>>name;
    socketStream>>passwdLen;
    if(passwdLen<0||passwdLen>MAX_STR_LEN)
    {
        socketStream<<FAULT;
        return 0;
    }
    passwd.resize(passwdLen);
    socketStream>>passwd;
    qDebug()<<"user name"<<name<<"passwd:"<<passwd;
    db->Reg(name,passwd);
    socketStream<<SUCCEED;
    return true;
}
