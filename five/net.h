#ifndef NET_H
#define NET_H

#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QErrorMessage>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include "../Public.h"
#define PORT 8910

struct Connection {
    quint16 port;
    QHostAddress add;
};

class Net :public QObject
{
    Q_OBJECT
public:
    Net(QString name, QString add, QString port,QString type);
    void senddata(QString str);
    bool IsListening();
    void listen();
    bool connectto(QString add, QString port);
    bool beServer(QString port);
public slots:
    void readdata();
    void newTcpConnect();
    void onSocketError(QAbstractSocket::SocketError s);
signals:
    void has_data(QString *);
    void has_err(QString );
    void startGame();
private:
    /*QUdpSocket *udp;
    struct Connection conn;*/
    QTcpServer *server;
    QTcpSocket *socket;
    QString data;
};

#endif // NET_H
