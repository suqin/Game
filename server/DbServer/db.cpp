#include "db.h"

DB::DB()
{
    *db = QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName("123.db");
    qDebug()<<db->open();
}

