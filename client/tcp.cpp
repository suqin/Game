#include "tcp.h"

Tcp::Tcp(QObject *parent) :
    QObject(parent)
{
    stream.setVersion(QDataStream::Qt_4_8);
    socket=new QTcpSocket(this);
    server = new QTcpServer(this);
    if(!server->listen(QHostAddress::Any,GAMEPORT))
    {
        QMessageBox box;
        box.setText(QString("请确保端口%1未被使用,无法作为主机").arg(GAMEPORT));
        box.exec();
        server->deleteLater();

    }
    if(!socket)
    {
        qDebug()<<__FUNCTION__<<"error";
        return ;
    }
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(server,SIGNAL(acceptError(QAbstractSocket::SocketError)),
            this,SLOT(onSocketError(QAbstractSocket::SocketError)));
    /*connect(server,SIGNAL(newConnection()),
            this,SLOT(hasNewConn()));*/
}
void Tcp::hasNewConn()
{



}

void Tcp::ConnectTo(QHostAddress *add, quint16 port)
{
    socket->connectToHost(*add,port);
}


bool Tcp::isOpen()
{
    return socket->isOpen();
}


QTcpSocket *Tcp::GetSocket()
{
    return socket;
}


void Tcp::onSocketError(QAbstractSocket::SocketError s)
{
    if(socket->error()==s)
        qDebug()<<socket->errorString();
    else
        qDebug()<<server->errorString();

}
void Tcp::Sed_Game_Req(QString name)
{

}


bool Tcp::login(QString name, QString passwd)
{
    qDebug()<<__FUNCTION__<<"begin";
    stream.setDevice(socket);
    int resault;
    if(!isOpen())
        return 0;
    stream<<CMD_LOGIN;
    stream<<name.length();
    stream<<name;
    stream<<passwd.length();
    stream<<passwd;
    if(!socket->waitForReadyRead())
        return 0;
    stream>>resault;
    qDebug()<<__FUNCTION__<<resault;
    if(resault==SUCCEED)
    {
        if(socket->bytesAvailable())
            hasNewDate();
        connect(socket,SIGNAL(readyRead()),
                this,SLOT(hasNewDate()));
        return 1;
    }
    return 0;
}


void Tcp::hasNewDate()
{

    while(socket->bytesAvailable())
    {
        int cmd;
        stream>>cmd;
        qDebug()<<__FUNCTION__<<"CMD:"<<cmd;
        switch (cmd)
        {
        case VAL_USER:
            hasNewUser();
            break;
        case CMD_DEL_USER:
            DelUser();
        case CMD_GAME_REQ:
            GameReq();
            break;

        }
    }
}

void Tcp::GameReq()
{
    QStringList *list;
    QString ip;
    quint16 port;
    int len;
    QString name;
    stream>>ip>>port>>len;
    name.resize(len);
    stream>>name;
    qDebug()<<ip<<port<<name;
    list = new QStringList();
    list->append(name);
    list->append(ip);
    list->append(QString("%1").arg(port));
    list->append(QString("%1").arg(TYPE_CLIENT));
    emit startGame(list);
    qDebug()<<__FUNCTION__;

}

int Tcp::hasNewUser()
{
    struct User *user;
    quint32 ip;
    user = new struct User;
    int len;
    stream>>len;
    user->name.resize(len);
    stream>>user->name;
    stream>>ip;
    stream>>user->port;
    stream>>user->online;
    user->add.setAddress(ip);
    emit newUser(user);
    return 0;

}

Tcp::~Tcp()
{
    socket->close();
    delete socket;
}
void Tcp::DelUser()
{
    int length=0;
    QString name;
    stream>>length;
    name.resize(length);
    stream>>name;
    qDebug()<<name;
    emit delU(name);
}
bool Tcp::reg(QString name, QString passwd)
{
    qDebug()<<__FUNCTION__<<"begin";
    stream.setDevice(socket);
    int resault;
    if(!isOpen())
        return 0;
    stream<<CMD_REG;
    stream<<name.length();
    stream<<name;
    stream<<passwd.length();
    stream<<passwd;
    if(!socket->waitForReadyRead())
        return 0;
    stream>>resault;
    qDebug()<<__FUNCTION__<<resault;
    if(resault==SUCCEED)
    {

        return 1;
    }
    return 0;
}
