#ifndef DB_H
#define DB_H

#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
class Db : public QObject
{
    Q_OBJECT
public:
    explicit Db(QObject *parent = 0);
    void connectDatabase(QString file);
    bool IsMatch(QString name,QString passwd);
    bool Reg(QString name,QString passwd);
signals:
    
public slots:

private:
    QSqlDatabase database;
    
};

#endif // DB_H
