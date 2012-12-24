#ifndef NET_H
#define NET_H

#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QErrorMessage>
#include <QMessageBox>
#include <QDataStream>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include "../Public.h"

#define PORT 4321

struct Connection {
    quint16 port;
    QHostAddress add;
};

class Net :public QObject
{
    Q_OBJECT
public:
    Net(QString _name, QString IP, QString port, int type);
    void senddata(QString str);
    bool IsListening();
    void listen();
    bool connectto(QString add, quint16 port);
public slots:
    void readdata();
    void newTcpConnect();
    void onSocketError(QAbstractSocket::SocketError s);
signals:
    void has_data(QString *);
    void has_err(QString );
    void startGame();
private:
    QTcpServer *server;
    QTcpSocket *socket;
    QString data;
    QString name;
};

#endif // NET_H
