#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <myclass.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyClass* myClass = new MyClass();
    qDebug() << "Debug part 1";
    myClass->method();
    qDebug() << "Debug part 2";
    myClass->method();

    return a.exec();
}
