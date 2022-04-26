#ifndef ENTRYS_H
#define ENTRYS_H

#include <QObject>
#include "entry.h"

struct ErrDirNotFound: public std::exception {
    QString description;
    const char *what() const throw() {
        return "Directory not found";
    }
};

class Entrys : public QObject
{
Q_OBJECT
public:
    explicit Entrys(QObject *parent = nullptr);
    void setDir(QString dir, QString side);
    QVector<Entry*> getEntrys(QString side);
    Entry* getEntry(QString side, QString key);
    QString getPath(QString side);
protected:

signals:
private:
    QHash<QString, QString> hash_path;
    QHash<QString, QVector<Entry*>> hash_side_entry;
    void setList(QString side);
};

#endif // ENTRYS_H
