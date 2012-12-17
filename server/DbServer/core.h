#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "../../Public.h"
#include "net.h"
#include "db.h"
class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CORE_H
