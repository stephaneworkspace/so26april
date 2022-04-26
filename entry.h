#ifndef ENTRY_H
#define ENTRY_H

#include <QObject>
#include <QString>
#include <QDateTime>

class Entry : public QObject
{
Q_OBJECT
public:
    explicit Entry(QObject *parent = nullptr);
    Entry(QString name, int size_file, QDateTime date_last_change, mode_t mode);
    void setValue(QString name, int size_file, QDateTime date_last_change, mode_t mode);
    QString getName();
    QString getSizeString(int decimals);
    QString getDateLastChangeString();
signals:
private:
    QString name;
    int size_file;
    QDateTime date_last_change;
    mode_t mode;
};


#endif // ENTRY_H
