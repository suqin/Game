#ifndef PACKAGEREADER_H
#define PACKAGEREADER_H

#include <QObject>
#include "Public.h"
#include "userlist.h"
#include "db.h"
#include <QDataStream>
#include <QAbstractSocket>
class PackageReader : public QObject
{
    Q_OBJECT
public:
    explicit PackageReader(QObject *parent = 0);
    bool Login();
    bool Reg();
    int SendLists();
    void SendUser(QAbstractSocket *socket,struct User *user);
    void DeleteUser(QAbstractSocket *socket, QString &user);

signals:
    void GetSocketByName(QAbstractSocket *socket,QString name);
    void LogSucceed(struct User *);
public slots:
    void ReadData(QAbstractSocket *socket,UserList *);

private:
    QAbstractSocket *s;
    UserList *l;
    Db *db;
};

#endif // PACKAGEREADER_H
