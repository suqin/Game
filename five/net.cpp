#include "net.h"

void Net::senddata(QString str)
{
    socket->write(str.toAscii());
}

Net::Net(QString name, QString add, QString port, QString type)
{
    if(type.toInt()==TYPE_SERVER)
        beServer(port);
    else
        connectto(add);
}

void Net::listen()
{
    if(!server->listen(QHostAddress::Any,PORT))
    {
        QMessageBox box;
        box.setText(QString("请确保端口%1未被使用").arg(PORT));
        box.exec();
        return ;
    }
    connect(server,SIGNAL(newConnection()),this,SLOT(newTcpConnect()));
}

void Net::newTcpConnect()
{
    if(server->hasPendingConnections())
    {
        socket=server->nextPendingConnection();
        //QString peerName=QString("与%1:%2的TCP连接").arg(socket->peerAddress().toString()).arg(socket->peerPort());
        /*int r=QMessageBox::question(NULL,QString(""),QString("").arg(peerName),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(QMessageBox::Yes!=r)
            {
                socket->abort();
                return ;
            }*/
        connect(socket,SIGNAL(readyRead()),this,SLOT(readdata()));
        connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onSocketError(QAbstractSocket::SocketError)));
        emit startGame();
        server->close();
    }
}

void Net::onSocketError(QAbstractSocket::SocketError s)
{
    qDebug()<<socket->errorString();
    emit has_err(socket->errorString());
}

void Net::readdata()
{
    QByteArray buff;
    buff.resize(socket->readBufferSize());
    buff.append(socket->readAll());
    data=QString::fromAscii(buff.data());
    qDebug()<<buff;
     emit has_data(&data);
}
bool Net::IsListening()
{
    return server->isListening();
}

bool Net::connectto(QString add, QString port)
{
    socket = new QTcpSocket();
    socket->connectToHost(add,port);
    if(socket->isOpen()) {
        connect(socket,SIGNAL(readyRead()),this,SLOT(readdata()));
        connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onSocketError(QAbstractSocket::SocketError)));
        emit startGame();
        server->close();
        return 1;
    }
    else {
        delete socket;
        emit has_err("无法连接接到主机");
        return 0;
    }
}
bool Net::beServer(QString port)
{
    /*server = new QTcpServer();
    if(!server->listen(QHostAddress::Any,PORT))
    {
        QMessageBox box;
        box.setText(QString("请确保端口%1未被使用").arg(PORT));
        box.exec();
        server->deleteLater();
        return 0;
    }
    connect(server,SIGNAL(newConnection()),this,SLOT(newTcpConnect()));*/
    return 1;
}
