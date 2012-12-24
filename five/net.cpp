#include "net.h"

void Net::senddata(QString str)
{
    socket->write(str.toAscii());
}

Net::Net(QString _name, QString IP, QString port, int type)
{
    QMessageBox box;
    name = _name;

    if(type == TYPE_SERVER)
    {
        if(connectto(GAMESERVERIP,GAMESERVERPORT))  //连接到服务器，发送游戏请求
        {
            QByteArray buff;
            QDataStream BuffStream(&buff,QIODevice::WriteOnly);
            BuffStream.setVersion(QDataStream::Qt_4_8);
            QDataStream SocStream(socket);
            SocStream.setVersion(QDataStream::Qt_4_8);
            BuffStream<<CMD_GAME_REQ<<name.size()<<name<<PORT;
            qDebug()<<socket->write(buff);

            qDebug()<<name<<IP<<port<<type;
        }
        else
        {
            box.setText(QString("网络错误"));
            box.exec();
            exit(-1);
        }
        socket->waitForBytesWritten();
        listen();
    }
    else
    {
        socket = new QTcpSocket(this);
        socket->connectToHost(IP,PORT);
        if(!socket->waitForConnected())
        {
            qDebug()<<__FUNCTION__<<"error";
            box.setText(QString("无法连接到主机"));
            box.exec();
            exit(-2);
        }
        connect(socket,SIGNAL(readyRead()),this,SLOT(readdata()));
        emit startGame();
        box.setText(QString("连接成功"));
        box.exec();

    }

}

void Net::listen()
{
    server = new QTcpServer();
    QMessageBox box;
    if(!server->listen(QHostAddress::Any,PORT))
    {

        box.setText("无法监听端口");
        box.exec();
        return ;
    }
    connect(server,SIGNAL(newConnection()),this,SLOT(newTcpConnect()));
    if(!server->waitForNewConnection(10000))
    {
        box.setText(QString("对方无响应"));
        box.exec();
        exit(-3);
    }
}

void Net::newTcpConnect()
{
    //socket->close();
    //socket->deleteLater();
    socket = server->nextPendingConnection();
    connect(socket,SIGNAL(readyRead()),this,SLOT(readdata()));
    emit startGame();
    QMessageBox box;
    box.setText("游戏开始");
    box.exec();

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
    data+=(buff.data());
    qDebug()<<buff;
    emit has_data(&data);
}
bool Net::IsListening()
{
    return server->isListening();
}

bool Net::connectto(QString add, quint16 port)
{
    socket = new QTcpSocket();
    socket->connectToHost(add,port);
    if(socket->isOpen()) {
        //connect(socket,SIGNAL(readyRead()),this,SLOT(readdata()));
        connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onSocketError(QAbstractSocket::SocketError)));
        return 1;
    }
    else {
        socket->deleteLater();
        qDebug()<<__FUNCTION__<<"无法连接接到主机";
        emit has_err("can not connect to host");
        return 0;
    }
}




