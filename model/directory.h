#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <QObject>
#include <QException>
#include <QVector>

#include "image.h"


class Directory : public QObject
{
    Q_OBJECT

public:
    using container = QVector<Image>;

    using iterator       = container::iterator;
    using const_iterator = container::const_iterator;
    using size_type      = container::size_type;


    Directory(const QStringList &mFormats);

    void open(const QString &path);
    void close();

    void scan();

    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend()   const;

    QString getPath() const;

    size_type count() const;


signals:
    void scanned();

private:
    QString mPath;
    container mImages;

    QStringList mFormats;
};

#endif // DIRECTORY_H
