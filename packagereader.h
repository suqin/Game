#ifndef PACKAGEREADER_H
#define PACKAGEREADER_H

#include <QObject>
#include "Public.h"
#include "userlist.h"
#include <QDataStream>
#include <QAbstractSocket>
class PackageReader : public QObject
{
    Q_OBJECT
public:
    explicit PackageReader(QObject *parent = 0);
    bool Login();
    int SendList();
    int GameRequest();
signals:
    void GetSocketByName(QAbstractSocket *socket,QString name);
public slots:
    void ReadData(QAbstractSocket *socket,UserList *);

private:
    //QDataStream socketStream;
    QAbstractSocket *s;
    UserList *l;
};

#endif // PACKAGEREADER_H
