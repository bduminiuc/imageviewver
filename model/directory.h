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



    class FilesNotFoundException : public QException
    {
    public:
        void raise() const override;
        FilesNotFoundException *clone() const override;
    };



    Directory(const QStringList &mFormats);

    void open(const QString &path);
    void close();

    void scan();

    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend()   const;

    QString getPath() const;


signals:
    void scanned();

private:
    QString mPath;
    container mImages;

    QStringList mFormats;
};

#endif // DIRECTORY_H
