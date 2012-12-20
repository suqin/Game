#include "db.h"

Db::Db(QObject *parent) :
    QObject(parent)
{
    connectDatabase("db.db");
}

void Db::connectDatabase(QString file)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(file);
    if(!database.open())
    {
        qDebug()<<__FUNCTION__<<"fail";
    }
    QSqlQuery query;
    query.exec("create table Info(name varchar,passwd varchar)");
}
bool Db::IsMatch(QString name, QString passwd)
{
    QString sql=QString("select * from Info where name='%1' and passwd='%2'").arg(name).arg(passwd);
    QSqlQuery query;
    query.exec(sql);
    qDebug()<<__FUNCTION__<<sql;
    if(!query.next())
        return 0;
    return 1;

}

bool Db::Reg(QString name, QString passwd)
{
    QString sql=QString("insert into Info values (%1,%2)").arg(name).arg(passwd);
    QSqlQuery query;
    return query.exec(sql);
}

