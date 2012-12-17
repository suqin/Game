#ifndef NET_H
#define NET_H

#include <QObject>
#include <QtNetwork>
#include "../../Public.h"
class Net : public QObject
{
    Q_OBJECT
public:
    explicit Net(QObject *parent = 0);
    
signals:
    
public slots:
private:
    QTcpServer *serverSocket;
    
};

#endif // NET_H
