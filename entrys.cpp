#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <QDebug>
#include <iostream>
#include <QDateTime>
#include <QProcess>
#include "entry.h"
#include "entrys.h"

Entrys::Entrys(QObject *parent)
        : QObject{parent}
{

}

void Entrys::setList(QString side) {
    QVector<Entry*> vec_entry;
    QString path = this->getPath(side);
    QByteArray path_ba = path.toLocal8Bit();
    const char* path_cstr = path_ba.constData();
    struct dirent *lecture;
    DIR *dir;
    struct stat buf;
    QString currentPath;
    int row = 0;

    dir = opendir(path_cstr);
    if (dir == NULL) {
        ErrDirNotFound e;
        QString description = "Path " + path + " don't exist !";
        e.description = description;
        throw e;
    }

    while ((lecture = readdir(dir)) != NULL) {
        if (strcmp(lecture->d_name, ".") != 0) {
            currentPath = path + lecture->d_name;
            QByteArray path_qb = currentPath.toLocal8Bit();
            const char *charCurrentPath = path_qb.constData();
            if ((stat(charCurrentPath, &buf)) == -1) {
                qCritical() << "stat" << currentPath;
            }
            int size = buf.st_size;
            QDateTime modif = QDateTime::fromSecsSinceEpoch(buf.st_mtime);
            Entry *entry = new Entry();
            if (!strcmp(lecture->d_name, "..")) {
                if (this->getPath(side) != "/") {
                    entry->setValue(lecture->d_name, 0, modif, 0);
                }
            } else {
                if (S_ISDIR(buf.st_mode)) {
                    QString qstringTemp = lecture->d_name;
                    qstringTemp += "/";
                    entry->setValue(qstringTemp, 0, modif, buf.st_mode);
                } else {
                    entry->setValue(lecture->d_name, size, modif, buf.st_mode);
                }
            }
            vec_entry.append(entry);
            row++;
        }
    }
    delete lecture;
    closedir(dir);
    this->hash_side_entry.insert(side, vec_entry);
}

void Entrys::setDir(QString dir, QString side) {
    this->hash_path.insert(side, dir);
    this->setList(side);
}


QVector<Entry*> Entrys::getEntrys(QString side) {
    return this->hash_side_entry.take(side);
}

QString Entrys::getPath(QString side) {
    return this->hash_path[side];
}

Entry* Entrys::getEntry(QString side, QString key) {
    QVector<Entry*> entry = this->getEntrys(side);
    for (int i = 0; i < entry.length(); i++) {
        if (entry[i]->getName() == key) {
            return entry[i];
        }
    }
    return nullptr;
}
