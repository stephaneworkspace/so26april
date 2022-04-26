#include "myclass.h"

#include <iostream>
#include "myclass.h"
#include "entry.h"
#include "entrys.h"

MyClass::MyClass(QObject *parent) : QObject(parent) {
    this->entrys = new Entrys();
    try {
        this->entrys->setDir("/Users/","L");
    } catch(ErrDirNotFound &e) {
        qDebug() << e.description << " " << e.what();
    }
}

void MyClass::method() {
    int i = 0;
    qDebug() << i;
    foreach(Entry *v, this->entrys->getEntrys("L")) {
        i++;
        qDebug() << i << v->getName() << " " << v->getSizeString(2) << " " << v->getDateLastChangeString();
    }
}


