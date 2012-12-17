#ifndef DB_H
#define DB_H
#include <QtSql>
#include "../../Public.h"
class DB
{
private:
    QSqlDatabase *db;

public:
    DB();
};

#endif // DB_H
