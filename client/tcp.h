#ifndef TCP_H
#define TCP_H
#include <QMainWindow>
#include <QObject>
#include <QtNetwork>
#include <QDataStream>
#include <QMessageBox>
#include "../userlist.h"
#include "../Public.h"
class Tcp : public QObject
{
    Q_OBJECT
public:
    explicit Tcp(QObject *parent = 0);
    void ConnectTo(QHostAddress *add,quint16 port);
    bool isOpen();
    bool login(QString &name,QString &passwd);
    bool reg(QString &name,QString &passwd);
    int hasNewUser();
    QTcpSocket *GetSocket();
    ~Tcp();
    void hasNewConn();
    void Sed_Game_Req(QString name);
    void DelUser();
signals:
    void newUser(struct User *);
    void delU(QString name);
public slots:
    void onSocketError(QAbstractSocket::SocketError s);
    void hasNewDate();

private:
    QTcpSocket *socket;
   //QTcpSocket *conn;
    QTcpServer *server;
    QDataStream stream;
    
};

#endif // TCP_H
