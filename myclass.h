#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include "entrys.h"

class MyClass : public QObject
{
Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr);
    void method();
signals:
private:
    Entrys* entrys;
};


#endif // MYCLASS_H
