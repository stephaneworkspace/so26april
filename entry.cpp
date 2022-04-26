#include <QDateTime>
#include "entry.h"

Entry::Entry(QObject *parent)
        : QObject{parent}
{

}

Entry::Entry(QString name, int size_file, QDateTime date_last_change, mode_t mode)
{
    this->name = name;
    this->size_file = size_file;
    this->date_last_change = date_last_change;
    this->mode = mode;
}

void Entry::setValue(QString name, int size_file, QDateTime date_last_change, mode_t mode)
{
    this->name = name;
    this->size_file = size_file;
    this->date_last_change = date_last_change;
    this->mode = mode;
}

QString Entry::getName()
{
    return this->name;
}

QString Entry::getSizeString(int decimals) {
    int bytes = this->size_file;
    if (bytes == 0) return "0 Bytes";
    const int K = 1024;
    const QStringList SIZES = { "Bytes", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
    const int I =  std::floor((std::log(bytes) / std::log(K)));
    int dm = decimals < 0 ? 0 : decimals;
    if (I == 0) dm = 0;
    return QString::number((bytes / std::pow(K, I)),'f', dm) + " " + SIZES[I];
}

QString Entry::getDateLastChangeString() {
    return this->date_last_change.toString("dd.MM.yyyy hh:mm:ss");
}
